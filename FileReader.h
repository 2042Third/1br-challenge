//
// Created by Mike Yang on 2024/6/20.
//

#ifndef ONEBILLIONROWS_FILEREADER_H
#define ONEBILLIONROWS_FILEREADER_H


#include <string>
#include <map>
#include "cc20_file.h"
#include "City.h"

class FileReader {

public:

  FileReader();
  ~FileReader();
  uint8_t* open_file (const char * file);
  bool get_next_line(std::string& line);
  std::tuple<std::string, double> parseLine(const std::string& line);
  bool next_line_parse(std::string_view& first, double& second) ;
  cc20_file r_file;
  char* stream;

  uint64_t currentPos = 0;
  uint64_t fileSize = 0;

//  struct cstring_hash {
//    size_t operator()(const char* str) const {
//      size_t hash = 5381;
//      while (*str) {
//        hash = ((hash << 5) + hash) + (*str++);
//      }
//      return hash;
//    }
//  };
//
//  struct cstring_equal {
//    bool operator()(const char* s1, const char* s2) const {
//      return strcmp(s1, s2) == 0;
//    }
//  };

//  std::unordered_map<const char*, City,cstring_hash,cstring_equal> city_map;
  std::unordered_map<std::string, City> city_map;

private:
  char one;
  char* lineStart;
  char* lineEnd;
  char* semicolon;
  size_t idx;
  char city [100] = {0};
  char num [100] = {0};

};


#endif //ONEBILLIONROWS_FILEREADER_H
