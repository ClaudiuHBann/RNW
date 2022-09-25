#pragma once

#include "pch.h"
#include "NativeModules.h"

#include "Command.h"
#include "Utility.hpp"

REACT_MODULE(SpeechRecognition);
struct SpeechRecognition
{
  SpeechRecognizer mSpeechRecognizer;
  vector<tuple<string, Command::DetectionLevel, function<void()>>> mCommands;

  mutex mMutex;

  REACT_METHOD(Initialize);
  fire_and_forget Initialize(const function<void()> callback) noexcept {
    co_await resume_background();

    mSpeechRecognizer.Timeouts().BabbleTimeout(TimeSpan(0));
    co_await mSpeechRecognizer.CompileConstraintsAsync();

    callback();
  }

  REACT_METHOD(Start);
  fire_and_forget Start(const function<void(string)> callback) noexcept {
    co_await resume_background();

    const auto speechRecognitionResult = co_await mSpeechRecognizer.RecognizeAsync();
    const auto command = to_string(speechRecognitionResult.Text());

    CommandCheck(command);
    callback(command);
  }

  REACT_METHOD(CommandAdd);
  fire_and_forget CommandAdd(const string command, const uint8_t commandDetectionLevel, const function<void()> callback) noexcept {
    co_await resume_background();

    scoped_lock lock(mMutex);
    mCommands.push_back({ Utility::ToUpper(command), (Command::DetectionLevel)commandDetectionLevel, callback });
  }

  REACT_METHOD(CommandChange);
  fire_and_forget CommandChange(const string commandOld, const uint8_t commandDetectionLevelOld, const string commandNew, const uint8_t commandDetectionLevelNew, const function<void()> callback) noexcept {
    co_await resume_background();

    scoped_lock lock(mMutex);
    const auto& it = find_if(mCommands.begin(), mCommands.end(), [detectionLevel = (Command::DetectionLevel)commandDetectionLevelOld, commandToUpper = Utility::ToUpper(commandOld)](const auto& tuple) {
      return commandToUpper == get<0>(tuple) && detectionLevel == get<1>(tuple);
    });
    if (it != mCommands.end()) {
      get<0>(*it) = Utility::ToUpper(commandNew);
      get<1>(*it) = (Command::DetectionLevel)commandDetectionLevelNew;
      get<2>(*it) = callback;
    }
  }

  REACT_METHOD(CommandRemove);
  fire_and_forget CommandRemove(const string command, const uint8_t commandDetectionLevel) noexcept {
    co_await resume_background();

    scoped_lock lock(mMutex);
    const auto& it = find_if(mCommands.begin(), mCommands.end(), [detectionLevel = (Command::DetectionLevel)commandDetectionLevel, commandToUpper = Utility::ToUpper(command)](const auto& tuple) {
      return commandToUpper == get<0>(tuple) && detectionLevel == get<1>(tuple);
    });
    if (it != mCommands.end()) {
      mCommands.erase(it);
    }
  }

  REACT_METHOD(CommandClear);
  fire_and_forget CommandClear() noexcept {
    co_await resume_background();

    scoped_lock lock(mMutex);
    mCommands.clear();
  }

  void CommandCheck(const string& command) {
    const auto commandToUpper = Utility::ToUpper(command);
    if (commandToUpper.empty()) {
      return;
    }

    scoped_lock lock(mMutex);
    const auto& it = find_if(mCommands.begin(), mCommands.end(), [&](const auto& tuple) {
      const auto& command = get<0>(tuple);
      const auto& detectionLevel = get<1>(tuple);

      return Command::IsDetectionLevel(command, commandToUpper, detectionLevel);
    });

    if (it != mCommands.end()) {
      get<2>(*it)();
    }
  }
};

/*
    TO DO:
            - !!! Find out why the fuck you can't invoke the same callback 2 times in this framework !!! (we did a workaround in react native for this shit)
            - Let react native see the Command::DetectionLevel enum
            - Check the command detection level logic with unusual examples
            - Stop method ?
            - check the method parameters (don't make copies or things like that)
            - create a method for finding a specific command in the command class
            -
*/