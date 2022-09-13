#pragma once

#include "pch.h"

#include <winrt/Windows.Media.SpeechRecognition.h>
#include <functional>

#include "NativeModules.h"

REACT_MODULE(SpeechRecognition);
struct SpeechRecognition
{
  REACT_METHOD(Listen);
  ::winrt::fire_and_forget Listen(::std::function<void(::std::string)> callback) noexcept {
    co_await ::winrt::resume_background();

    static ::winrt::Windows::Media::SpeechRecognition::SpeechRecognizer speechRecognizer = nullptr;
    if (!speechRecognizer) {
      speechRecognizer = ::winrt::Windows::Media::SpeechRecognition::SpeechRecognizer();
      co_await speechRecognizer.CompileConstraintsAsync();
    }

    auto speechRecognitionResult = co_await speechRecognizer.RecognizeAsync();
    callback(to_string(speechRecognitionResult.Text()));
  }
};
