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

  // small callback for the function for the shit workaround
  var createCommandCallback = (text, detectionLevel) => {
    setTextMe('Command: ' + text + ', DetectionLevel: ' + detectionLevel);

    // reset the callback
    SpeechRecognition.CommandChange(
      text,
      detectionLevel,
      text,
      detectionLevel,
      () => {
        createCommandCallback(text, detectionLevel);
      },
    );
  };

  // small function for the shit workaround
  var createCommand = (text, detectionLevel) => {
    SpeechRecognition.CommandAdd(text, detectionLevel, () => {
      createCommandCallback(text, detectionLevel);
    });
  };

  // the callback function to be called when a speech recognition completed
  var callback = text => {
    // set a default text if you said nothing
    if (text == '') {
      text = 'Listening...';
      //setTextMe('Nothing...');
    }

    // update UI and listen again
    setTextYou(text);
    SpeechRecognition.Start(callback);
  };

  // run this function once (it's a loop)
  useEffect(() => {
    SpeechRecognition.CommandClear();

    // e.g.: say anything bcz it doesnt matter
    createCommand('do something', 0);
    SpeechRecognition.CommandRemove('do something', 0);

    // e.g.: say "what the hell is flying up there"
    createCommand('what is up', 1);

    // e.g.: say "freak get out"
    createCommand('get out freak', 2);

    // e.g.: say "damn what is this garbage"
    createCommand('what is this', 3);

    // e.g.: say "say something"
    createCommand('say something', 4);

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
        Last Command:
      </Text>
      <Text style={{flexWrap: 'wrap', fontSize: 18, textAlign: 'center'}}>
        {textMe}
      </Text>
    </View>
  );
};

export default App;
