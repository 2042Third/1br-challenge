#include <iostream>
#include "cc20_file.h"
#include "FileReader.h"

int main() {

  FileReader fr;
  fr.open_file("./measurements.txt");

  bool has_next = true;

  std::string line;
  fr.get_next_line(line);

  uint64_t count = 0;

  std::string_view first;
  double second;

  size_t limit = 10000000;

  while (fr.next_line_parse(first, second)) {
    count++;
    if (count >= limit){
      break;
    }
  }


  std::cout << "Total lines: " << count << std::endl;

  std::cout << "Unique Cities: " << fr.city_map.size() << std::endl;

  for (const auto &itm:fr.city_map) {
    std::cout << itm.first << "/" << itm.second.min
    << "/" << itm.second.total / itm.second.count
    << "/" << itm.second.max << std::endl;
  }

  return 0;
}
