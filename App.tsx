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
      //setTextMe('Nothing...');
    }

    // update UI and listen again
    setTextYou(text);
    SpeechRecognition.Start(callback);
  };

  // run this function once (it's a loop)
  useEffect(() => {
    // e.g.: say anything bcz it doesnt matter
    SpeechRecognition.CommandAdd('do something', 0, () => {
        setTextMe('NaNi !?');
    });
    
    // e.g.: say "what the hell is flying up there"
    SpeechRecognition.CommandAdd('what is up', 1, () => {
        setTextMe('Detected command of level 1.');
    });
    
    // e.g.: say "freak get out"
    SpeechRecognition.CommandAdd('get out freak', 2, () => {
        setTextMe('Detected command of level 2.');
    });
    
    // e.g.: say "damn what is this garbage"
    SpeechRecognition.CommandAdd('what is this', 3, () => {
        setTextMe('Detected command of level 3.');
    });
    
    // e.g.: say "say something"
    SpeechRecognition.CommandAdd('say something', 4, () => {
      setTextMe('Detected command of level 4.');
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
