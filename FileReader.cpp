//
// Created by Mike Yang on 2024/6/20.
//

#include <cstdint>
#include <iostream>
#include <charconv>
#include "FileReader.h"

FileReader::FileReader() {
  // Constructor
  city_map.reserve(10001);

}

FileReader::~FileReader() {
  // Destructor
  r_file.unmap();
}

uint8_t* FileReader::open_file (const char * file) {
  r_file.read_new(file);
  stream = (char*) r_file.get_mapping();
  fileSize = r_file.file_size();

  return (uint8_t*) stream;
}

bool FileReader::get_next_line(std::string& line) {
  if (currentPos >= fileSize) {
    return false;
  }

  size_t lineStart = currentPos;
  while (currentPos < fileSize && stream[currentPos] != '\n') {
    currentPos++;
  }

  line = std::string(reinterpret_cast<char*>(stream + lineStart), currentPos - lineStart);

  if (currentPos < fileSize) {
    currentPos++; // Skip the newline character
  }

  return true;
}


std::tuple<std::string, double> FileReader::parseLine(const std::string& line) {
  size_t pos = line.find(';');
  if (pos == std::string::npos) {
    throw std::runtime_error("Invalid line format: missing semicolon");
  }

  std::string first = line.substr(0, pos);

  try {

    double second = std::stod(line.substr(pos + 1));
    return std::make_tuple(std::move(first), second);
  } catch (const std::invalid_argument& e) {
    throw std::runtime_error("Invalid line format: second part is not a valid float");
  } catch (const std::out_of_range& e) {
    throw std::runtime_error("Invalid line format: float value out of range");
  }
}


bool FileReader::next_line_parse(std::string_view& first, double& second) {
  if (currentPos >= fileSize) {
    return false;
  }

  lineStart = stream + currentPos;
  lineEnd = lineStart;
  semicolon = nullptr;
  idx =0;

  while (lineEnd < stream + fileSize && *lineEnd != '\n') {
    one = *lineEnd;
    if (!semicolon) {
      if (one == ';' ) {
        semicolon = lineEnd;
        city[idx] = '\0';
      }
      else {
        city[idx] = one;
      }
    }
    else {
      num[idx - (semicolon - lineStart+1)] = one;
    }
    lineEnd++;
    idx++;
  }
  num[idx] = '\0';


  if (!semicolon) {
    currentPos = lineEnd - stream + 1; // Skip this invalid line
    throw std::runtime_error("Invalid line format: missing semicolon");
  }


//  first = std::string_view(city, semicolon - lineStart);

  char* numberEnd;
  errno = 0;
  second = std::strtod(num, &numberEnd);
  city_map[city] += second;

//  if (numberEnd == num) {
//    currentPos = lineEnd - stream + 1; // Skip this invalid line
//    throw std::runtime_error("Invalid line format: second part is not a valid double");
//  } else if (errno == ERANGE) {
//    currentPos = lineEnd - stream + 1; // Skip this invalid line
//    throw std::runtime_error("Invalid line format: double value out of range");
//  }

  currentPos = lineEnd - stream + 1; // Move to the next line
  return true;
}