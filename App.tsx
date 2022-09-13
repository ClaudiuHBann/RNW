/**
 * @format
 * @flow strict-local
 */

import React, { useState, useEffect } from 'react';
import type { Node } from 'react';
import { Text, View } from 'react-native';

import SpeechRecognition from './SpeechRecognition';

const App: () => Node = () => {
  // for binding the speech recognition text to the text control
  const [text, setText] = useState("Listening...");

  // the callback function to be called when a speech recognition completed
  var callback = (text) => {
    // set a default text if you said nothing
    if (text == "") {
      text = "Listening...";
    }

    // update UI and listen again
    setText(text);
    SpeechRecognition.Listen(callback);
  };

  // run this function once (it's a loop)
  useEffect(() => {
    SpeechRecognition.Listen(callback);
  }, []);

  // create a smol UI to see the results
  return (
    <View style={{ justifyContent: 'center', height:"100%" }}>
      <Text style={{ fontSize: 25, textAlign: "center", marginBottom: "2%" }}>You said:</Text>
      <Text style={{ flexWrap: 'wrap', fontSize: 18, textAlign: "center" }}>{text}</Text>
    </View>
  );
};

export default App;
