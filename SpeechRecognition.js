/**
 * @flow
 * @format
 */

 import type {TurboModule} from 'react-native/Libraries/TurboModule/RCTExport';
 import * as TurboModuleRegistry from 'react-native/Libraries/TurboModule/TurboModuleRegistry';
 
 export interface Spec extends TurboModule {
   +Listen: (callback: (text: string) => void) => void;
 }
 
 export default (TurboModuleRegistry.getEnforcing<Spec>(
   'SpeechRecognition',
 ): Spec);
 