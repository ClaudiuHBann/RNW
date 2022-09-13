/**
 * @format
 * @flow strict-local
 */

import React, { useState, useEffect } from 'react';
import type { Node } from 'react';
import { Text, View } from 'react-native';

import SpeechRecognition from './SpeechRecognition';

const App: () => Node = () => {
  const [text, setText] = useState("Listening...");

  var callback = (text) => {
    if (text == "") {
      text = "Listening...";
    }

    setText(text);
    SpeechRecognition.Listen(callback);
  };

  useEffect(() => {
    SpeechRecognition.Listen(callback);
  }, []);

  return (
    <View style={{ justifyContent: 'center', height:"100%" }}>
      <Text style={{ fontSize: 25, textAlign: "center", marginBottom: "2%" }}>You said:</Text>
      <Text style={{ flexWrap: 'wrap', fontSize: 18, textAlign: "center" }}>{text}</Text>
    </View>
  );
};

export default App;
