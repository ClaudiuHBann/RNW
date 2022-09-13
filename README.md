
# React Native Windows

This is a speech recognition example using react native windows framework and native modules.

## How does it work

1. Create the default react native windows project like in [here](https://docs.microsoft.com/en-us/windows/dev-environment/javascript/react-native-for-windows)
2. Create a file in the C++ project which will contain the speech recognition code like in [here](https://github.com/ClaudiuHBann/RNW/blob/master/windows/RNW/SpeechRecognition.hpp)
3. Link the C++ file in the C++ project like in [here](https://github.com/ClaudiuHBann/RNW/blob/master/windows/RNW/ReactPackageProvider.cpp)
4. Create the JS file which will contain the C++ methods and properties in react native like in [here](https://github.com/ClaudiuHBann/RNW/blob/master/SpeechRecognition.js)
5. Link the JS file in the react native project like in [here](https://github.com/ClaudiuHBann/RNW/blob/master/index.js)
6. Create a simple test to see the result like in [here](https://github.com/ClaudiuHBann/RNW/blob/master/App.tsx)

## Try it yourself
Create the project yourself with [this](https://docs.microsoft.com/en-us/windows/dev-environment/javascript/react-native-for-windows)
OR
just run the "npm install" command in the RNW directory

## Watch out
1. When you create your react native project make sure you don't have any spaces in the absolute path to the project
2. Make sure you have Settings -> Privacy -> Speech -> Online speech recognition ON
3. Make sure you have C++ project -> Package.appxmanifest -> Capabilities -> Microphone ON
4. If you get an error or warning when installing the last react native use the "--version 0.68.2"  argument and value (or an older version depending on how much time has passed from this project's creation)
