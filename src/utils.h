#include <iostream>
#include <vector>
#include <iomanip>

std::ostream& operator<<(std::ostream& out, std::vector<int> v);
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& m);

