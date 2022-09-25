#pragma once

class Command
{
public:
  /*
        000
        . (first flag) -> command -> words
         . (middle flag) -> command's sequence == words's sequence
          . (last flag) -> command's length == words's length

        In the definitions below there is a Command - Words relation.
    */
  enum class DetectionLevel : uint8_t
  {
    NONE, // 000, e.g: "" - ""
    LOW, // 100, e.g: "WHAT IS UP" - "WHAT THE HELL IS FLYING UP THERE"
    MEDIUM_LOW, // 101, e.g: "GET THE FUCK OUT" - "THE FUCK GET OUT"
    MEDIUM_HIGH, // 110, e.g: "WHAT IS THIS" - "DAMN WHAT IS THIS SHIT"
    HIGH // 111, e.g: "SAY SOMETHING" - "SAY SOMETHING"
  };

  static inline const bool IsDetectionLevel(const string& command, const string& sentence, const DetectionLevel detectionLevel) {
    switch (detectionLevel) {
      case DetectionLevel::NONE:
        return false;

      case DetectionLevel::LOW:
        return ContainWords(command, sentence);

      case DetectionLevel::MEDIUM_LOW:
        return GetWordCount(command) == GetWordCount(sentence) && ContainWords(command, sentence);

      case DetectionLevel::MEDIUM_HIGH:
        return sentence.find(command) != string::npos;

      case DetectionLevel::HIGH:
        return command == sentence;

      default:
        return false;
    }
  }

  static void GetWords(const string& sentence, vector<string>& words);
  static const bool ContainWords(const string& toLookFor, const string& toBeLooked);

  static inline void GetWordCount(const string& sentence, map<string, size_t>& wordCount) {
    vector<string> words;
    GetWords(sentence, words);

    for (const auto& word : words) {
      wordCount[word]++;
    }
  }

  static inline const size_t GetWordCount(const string& sentence) {
    vector<string> words;
    GetWords(sentence, words);

    return words.size();
  }
};