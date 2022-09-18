/**
 * @flow
 * @format
 */

import type { TurboModule } from 'react-native/Libraries/TurboModule/RCTExport';
import * as TurboModuleRegistry from 'react-native/Libraries/TurboModule/TurboModuleRegistry';

export interface Spec extends TurboModule {
    +Initialize: (callback: () => void) => void;
    +Start: (callback: (text: string) => void) => void;
    +CommandAdd: (text: string, callback: () => void) => void;
}

export default (TurboModuleRegistry.getEnforcing < Spec > (
    'SpeechRecognition',
): Spec);