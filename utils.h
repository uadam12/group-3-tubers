#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

struct FileOperations {
  static std::fstream *openFile(const char *fileName) {
    std::fstream *textFile = new std::fstream();
    textFile->open(fileName);
    if (!textFile->is_open()) {
      throw std::string(fileName, " does not exist");
    }
    return textFile;
  }

  static std::vector<std::string>
  readFileIntoStringArray(std::fstream *textFile) {
    std::vector<std::string> result;
    std::string line;
    if (textFile->is_open()) {
      while (std::getline(*textFile, line, '\n')) {
        result.push_back(line);
      }
    }
    return result;
  }

  static std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
  }

  static std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        // Remove leading and trailing spaces from the token
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);

        tokens.push_back(token);
    }

    return tokens;
}

};

#endif // UTILS_H
