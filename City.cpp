#include "City.h"

void City::operator+=(double x) {
  total += x;
  if (x < min) {
    min = x;
  }
  if (x > max) {
    max = x;
  }
  count++;
}
