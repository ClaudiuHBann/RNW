#pragma once

#include "pch.h"

#include <winrt/Windows.Media.SpeechRecognition.h>
#include <mutex>
#include <tuple>

#include "NativeModules.h"

REACT_MODULE(SpeechRecognition);
struct SpeechRecognition
{
  /*
      000
      . (first flag) -> command -> words
       . (middle flag) -> command's sequence == words's sequence
        . (last flag) -> command's length == words's length

      In the below examples there is a Command - Words relation.
  */
  enum class CommandDetectionLevel : uint8_t
  {
    NONE, // 000, e.g: "" - ""
    LOW, // 100, e.g: "WHAT IS UP" - "WHAT THE HELL IS FLYING UP THERE"
    MEDIUM_LOW, // 101, e.g: "GET THE FUCK OUT" - "THE FUCK GET OUT"
    MEDIUM_HIGH, // 110, e.g: "WHAT IS THIS" - "DAMN WHAT IS THIS SHIT"
    HIGH // 111, e.g: "SAY SOMETHING" - "SAY SOMETHING"
  };

  ::winrt::Windows::Media::SpeechRecognition::SpeechRecognizer mSpeechRecognizer;
  ::std::vector<::std::tuple<::std::string, CommandDetectionLevel, ::std::function<void()>>> mCommands;

  ::std::mutex mMutex;

  REACT_METHOD(Initialize);
  ::winrt::fire_and_forget Initialize(const ::std::function<void()> callback) noexcept {
    co_await ::winrt::resume_background();

    mSpeechRecognizer.Timeouts().BabbleTimeout(TimeSpan(0));
    co_await mSpeechRecognizer.CompileConstraintsAsync();

    callback();
  }

  REACT_METHOD(Start);
  ::winrt::fire_and_forget Start(const ::std::function<void(::std::string)> callback) noexcept {
    co_await ::winrt::resume_background();

    auto speechRecognitionResult = co_await mSpeechRecognizer.RecognizeAsync();
    auto command = ::winrt::to_string(speechRecognitionResult.Text());

    CommandCheck(command);
    callback(command);
  }

  REACT_METHOD(CommandAdd);
  ::winrt::fire_and_forget CommandAdd(const ::std::string command, const uint8_t commandDetectionLevel, const ::std::function<void()> callback) noexcept {
    co_await ::winrt::resume_background();

    ::std::scoped_lock(mMutex);
    mCommands.push_back({ ToUpper(command), (CommandDetectionLevel)commandDetectionLevel, callback });
  }

  void CommandCheck(const ::std::string& command) {
    ::std::scoped_lock(mMutex);

    auto it = ::std::find_if(mCommands.begin(), mCommands.end(), [commandToUpper = ToUpper(command)](const auto& tuple) {
      const auto& command = ::std::get<0>(tuple);

      switch (::std::get<1>(tuple)) {
        case CommandDetectionLevel::NONE:
          return false;

        case CommandDetectionLevel::LOW:
          return false;

        case CommandDetectionLevel::MEDIUM_LOW:
          return false;

        case CommandDetectionLevel::MEDIUM_HIGH:
          return !commandToUpper.empty() && command.find(commandToUpper) != ::std::string::npos;

        case CommandDetectionLevel::HIGH:
          return command == commandToUpper;

        default:
          return false;
      }
    });

    if (it != mCommands.end()) {
      ::std::get<2>(*it)();
    }
  }

  ::std::string ToUpper(::std::string str) {
    ::std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
  }
};

/*
    TO DO:
            - !!! Find out why the fuck you can't call a callback 2 times in this framework !!!
            - Let react native see the CommandDetectionLevel enum
            - Resolve warnings and set the warning level to 4
            - CommandDetectionLevel::MEDIUM_HIGH what if the command can be composed with the before and after words from the sentence
            - Finish the CommandDetectionLevel MEDIUM_LOW and LOW implementations from the switch
            -
*/