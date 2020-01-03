#include "utils.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& out, std::vector<int> v) {
  for (const auto& val : v)
    out << std::setw(3) << val;

  return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& m) {
  for (const auto& row : m)
    out << row << std::endl;

  return out;
}
