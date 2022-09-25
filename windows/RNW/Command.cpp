#include "pch.h"
#include "Command.h"

const bool Command::ContainWords(const string& toLookFor, const string& toBeLooked) {
  if (GetWordCount(toBeLooked) < GetWordCount(toLookFor)) {
    return false;
  }

  map<string, size_t> wordsToLookFor;
  GetWordCount(toLookFor, wordsToLookFor);

  map<string, size_t> wordsToBeLookedFor;
  GetWordCount(toBeLooked, wordsToBeLookedFor);

  for (const auto& pairToLookFor : wordsToLookFor) {
    const auto& it = wordsToBeLookedFor.find(pairToLookFor.first);
    if (it != wordsToBeLookedFor.end()) {
      if (pairToLookFor.second <= it->second) {
        continue;
      } else {
        return false;
      }
    }

    return false;
  }

  return true;
}

void Command::GetWords(const string& sentence, vector<string>& words) {
  size_t last = 0, next = 0;
  while ((next = sentence.find(' ', last)) != string::npos) {
    const auto word = sentence.substr(last, next - last);
    if (!word.empty()) {
      words.push_back(word);
    }

    last = next + 1;
  }

  const auto word = sentence.substr(last);
  if (!word.empty()) {
    words.push_back(word);
  }
}