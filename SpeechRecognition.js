/**
 * @flow
 * @format
 */

import type {TurboModule} from 'react-native/Libraries/TurboModule/RCTExport';
import * as TurboModuleRegistry from 'react-native/Libraries/TurboModule/TurboModuleRegistry';

export interface Spec extends TurboModule {
  +Initialize: (callback: () => void) => void;
  +Start: (callback: (text: string) => void) => void;

  +CommandAdd: (
    text: string,
    detectionLevel: number,
    callback: () => void,
  ) => void;
  +CommandChange: (
    textOld: string,
    detectionLevelOld: number,
    textNew: string,
    detectionLevelNew: number,
    callback: () => void,
  ) => void;
  +CommandRemove: (text: string, detectionLevel: number) => void;
  +CommandClear: () => void;
}

export default (TurboModuleRegistry.getEnforcing<Spec>(
  'SpeechRecognition',
): Spec);
