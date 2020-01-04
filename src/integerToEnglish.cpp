// Integer to English - https://leetcode.com/problems/integer-to-english-words/
#include <iostream>
#include <vector>


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


std::vector<std::string> g_numbers = {
  "Zero",
  "One",
  "Two",
  "Three",
  "Four",
  "Five",
  "Six",
  "Seven",
  "Eight",
  "Nine",
  "Ten",
  "Eleven",
  "Twelve",
  "Thirteen",
  "Fourteen",
  "Fifteen",
  "Sixteen",
  "Seventeen",
  "Eighteen",
  "Nineteen"
};

std::vector<std::string> g_dec = {
  "zeroty",
  "onety",
  "Twenty",
  "Thirty",
  "Forty",
  "Fifty",
  "Sixty",
  "Seventy",
  "Eighty",
  "Ninety"
};

struct Groups {
  int num;
  std::string name;
};

std::vector<Groups> g_groups = {
  {1000000000, "Billion"},
  {1000000, "Million"},
  {1000, "Thousand"},
  {100, "Hundred"}
};



std::string g_hundreds = "Hundred";

class Solution {

public:

  std::string numberToWords(int num) {
    if (num == 0) {
      return g_numbers[0];
    }

    std::string result;
    for (const auto& group : g_groups) {
      int groupValue = num / group.num;
      if (groupValue != 0) {
        result += " " + numberToWords(groupValue) + " " + group.name;
        trim(result);
      }

      num = num % group.num;
    }

    result += " " + spell2Digits(num);

    trim(result);
    return result;
  }

  std::string spell2Digits(int num) {
    if (num == 0)
      return "";

    if (num < (int)g_numbers.size())
      return g_numbers[num];

    auto res = g_dec[num/10] + " " + spell2Digits(num % 10);
    trim(res);

    return res;
  }
};



static void test() {
  Solution s;

  std::cout << s.numberToWords(12345) << std::endl;

  assert(s.numberToWords(1) == "One");
  assert(s.numberToWords(2) == "Two");
  assert(s.numberToWords(9) == "Nine");
  assert(s.numberToWords(10) == "Ten");
  assert(s.numberToWords(11) == "Eleven");
  assert(s.numberToWords(19) == "Nineteen");
  assert(s.numberToWords(20) == "Twenty");
  assert(s.numberToWords(21) == "Twenty One");
  assert(s.numberToWords(29) == "Twenty Nine");
  assert(s.numberToWords(30) == "Thirty");
  assert(s.numberToWords(31) == "Thirty One");
  assert(s.numberToWords(99) == "Ninety Nine");
  assert(s.numberToWords(123) == "One Hundred Twenty Three");
  assert(s.numberToWords(12345) == "Twelve Thousand Three Hundred Forty Five");
  assert(s.numberToWords(1234567) == "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven");
  assert(s.numberToWords(1234567891) == "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One");
  assert(s.numberToWords(14) == "Fourteen");
  assert(s.numberToWords(1) == "One");
  assert(s.numberToWords(1) == "One");
}


