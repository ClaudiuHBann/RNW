#pragma once

#define NOMINMAX

// win32
#include <unknwn.h>
#include <windows.h>
#include <hstring.h>
#include <VersionMacros.h>
#include <CppWinRTIncludes.h>
#include <restrictederrorinfo.h>


// winrt windows/microsoft
#include <UI.Xaml.Markup.h>
#include <UI.Xaml.Controls.h>
#include <UI.Xaml.Navigation.h>
#include <UI.Xaml.Controls.Primitives.h>


// winrt windows
#include <winrt/Windows.Media.SpeechRecognition.h>
#include <winrt/Windows.ApplicationModel.Activation.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Media::SpeechRecognition;


// winrt microsoft
#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Automation.Peers.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>


// std
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <mutex>
#include <tuple>

using namespace std;