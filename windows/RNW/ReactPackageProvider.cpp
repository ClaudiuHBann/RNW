#include "pch.h"

// link the native module
#include "SpeechRecognition.hpp"

#include "ReactPackageProvider.h"
#include "NativeModules.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::RNW::implementation
{

  void ReactPackageProvider::CreatePackage(IReactPackageBuilder const& packageBuilder) noexcept
  {
    AddAttributedModules(packageBuilder);
  }

} // namespace winrt::RNW::implementation
