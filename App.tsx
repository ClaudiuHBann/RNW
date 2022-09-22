/**
 * @format
 * @flow strict-local
 */

import React, {useState, useEffect} from 'react';
import type {Node} from 'react';
import {Text, View} from 'react-native';

import SpeechRecognition from './SpeechRecognition';

const App: () => Node = () => {
  // for binding the speech recognition text to the text control
  const [textYou, setTextYou] = useState('Listening...');
  const [textMe, setTextMe] = useState('Nothing...');

  // the callback function to be called when a speech recognition completed
  var callback = text => {
    // set a default text if you said nothing
    if (text == '') {
      text = 'Listening...';
      setTextMe('Nothing...');
    }

    // update UI and listen again
    setTextYou(text);
    SpeechRecognition.Start(callback);
  };

  // run this function once (it's a loop)
  useEffect(() => {
    SpeechRecognition.CommandAdd('do something', 0, () => {
      setTextMe('fuck you');
    });

    SpeechRecognition.CommandAdd('swipe left', 3, () => {
      setTextMe('I swiped left.');
    });

    SpeechRecognition.CommandAdd('call 911', 4, () => {
      setTextMe('No thank you!');
    });

    SpeechRecognition.Initialize(() => {
      SpeechRecognition.Start(callback);
    });
  }, []);

  // create a smol UI to see the results
  return (
    <View style={{justifyContent: 'center', height: '100%'}}>
      <Text style={{fontSize: 25, textAlign: 'center', marginBottom: '2%'}}>
        You said:
      </Text>
      <Text
        style={{
          flexWrap: 'wrap',
          fontSize: 18,
          textAlign: 'center',
          marginBottom: '5%',
        }}>
        {textYou}
      </Text>

      <Text
        style={{
          fontSize: 25,
          textAlign: 'center',
          marginBottom: '2%',
          marginTop: '5%',
        }}>
        I said:
      </Text>
      <Text style={{flexWrap: 'wrap', fontSize: 18, textAlign: 'center'}}>
        {textMe}
      </Text>
    </View>
  );
};

export default App;
