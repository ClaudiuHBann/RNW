#pragma once

#include "pch.h"

#include <winrt/Windows.Media.SpeechRecognition.h>
#include <mutex>

#include "NativeModules.h"

REACT_MODULE(SpeechRecognition);
struct SpeechRecognition
{
  ::winrt::Windows::Media::SpeechRecognition::SpeechRecognizer mSpeechRecognizer;
  ::std::vector<::std::pair<::std::string, ::std::function<void()>>> mCommands;

  ::std::mutex mMutex;

  REACT_METHOD(Initialize);
  ::winrt::fire_and_forget Initialize(const ::std::function<void()> callback) noexcept {
    co_await ::winrt::resume_background();

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
  ::winrt::fire_and_forget CommandAdd(const ::std::string command, const ::std::function<void()> callback) noexcept {
    co_await ::winrt::resume_background();

    ::std::scoped_lock(mMutex);
    mCommands.push_back({ ToUpper(command), callback });
  }

  void CommandCheck(const ::std::string& command) {
    ::std::scoped_lock(mMutex);
    auto it = ::std::find_if(mCommands.begin(), mCommands.end(), [commandToUpper = ToUpper(command)](const auto& pair) {
      return pair.first == commandToUpper;
    });

    if (it != mCommands.end()) {
      it->second();
    }
  }

  ::std::string ToUpper(::std::string str) {
    ::std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
  }
};