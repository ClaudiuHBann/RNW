/**
 * @format
 */

import {AppRegistry} from 'react-native';
import App from './App';
import {name as appName} from './app.json';

// link the C++/WinRT module
import SpeechRecognition from './SpeechRecognition';
export { SpeechRecognition };

AppRegistry.registerComponent(appName, () => App);
