// https://leetcode.com/problems/fraction-to-recurring-decimal/
#include <iostream>
#include <map>


class Solution {
public:
  std::string fractionToDecimal(int num, int denom) {
    long long n = num;
    long long d = denom;

    if (num == 0)
      return "0";

    bool negative = false;
    if (n < 0) {
      n = -n;
      negative = !negative;
    }

    if (d < 0) {
      d = -d;
      negative = !negative;
    }

    long long whole = n / d;
    long long rem = n % d;

    rem *= 10;
    std::map<long long, int> reminders; // Already observed reminders and the position they occured.
    std::string decimal;
    while (rem) {
      auto remIt = reminders.find(rem);
      if (remIt != reminders.end()) {
        decimal.insert(remIt->second, "(");
        decimal.push_back(')');
        break;
      }

      reminders[rem] = decimal.size();
      long long newDigit = rem / d;
      decimal.push_back(newDigit + '0');

      // std::cout << "Rem=" << rem << "ND=" << newDigit << std::endl;     
      rem = rem % d;
      rem *= 10;
    }

    std::string result;
    if (negative)
      result += '-';
    result += std::to_string(whole);
    if (!decimal.empty())
      result += "." + decimal;

    return result;
  }
};




static void test() {
  std::cout << "Hello World!" << std::endl;

  Solution s;

  std::cout << "241/13 = 18.(538461), actual: " << s.fractionToDecimal(241, 13) << std::endl;
  std::cout << "1/2 = 0.5, actual: " << s.fractionToDecimal(1, 2) << std::endl;
  std::cout << "2/1 = 2, actual: " << s.fractionToDecimal(2, 1) << std::endl;
  std::cout << "2/3 = 0.(6), actual: " << s.fractionToDecimal(2, 3) << std::endl;
  std::cout << "-50/8 = -6.25, actual: " << s.fractionToDecimal(-50, 8) << std::endl;
  std::cout << "0/-5 = 0, actual: " << s.fractionToDecimal(0, -5) << std::endl;
  std::cout << "-1/-2147483648 = ?, actual: " << s.fractionToDecimal(-1, -2147483648) << std::endl;
}

