#pragma once

#include <string>
using namespace std;

class Utility
{
public:
  static string ToUpper(string str) {
    for (auto& c : str) {
      c = (char)toupper(c);
    }

    return str;
  }
};