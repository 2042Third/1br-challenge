
#include <cstdint>

class City {
public:
  double total = 0;
  void operator+=(double x);
  double min = 100;
  double max = -100;
  int64_t count = 1;

};