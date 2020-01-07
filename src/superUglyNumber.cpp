// https://leetcode.com/problems/super-ugly-number/
#include <iostream>
#include <vector>
#include <set>

class Solution {
public:
  int nthSuperUglyNumber(int n, const std::vector<int>& primes) {
    if (n == 0)
      return 0;

    std::set<long long> s;
    s.insert(1);

    long long result = 0;
    while (n) {
      result = *s.begin();
      s.erase(s.begin());

      for (int p : primes) {
        auto newNumber = result * p;
        if ((s.size() > (std::size_t)n) && (newNumber >= *s.rbegin()))
          break;

        s.insert(result * p);

      }

      --n;
    }
    
    return result;
  }
};


static void test() {
  Solution s;
  std::cout << s.nthSuperUglyNumber(100000, {7,19,29,37,41,47,53,59,61,79,83,89,101,103,109,127,131,137,139,157,167,179,181,199,211,229,233,239,241,251}) << std::endl;
  assert(s.nthSuperUglyNumber(12, {2,7,13,19}) == 32);
  assert(s.nthSuperUglyNumber(100000, {7,19,29,37,41,47,53,59,61,79,83,89,101,103,109,127,131,137,139,157,167,179,181,199,211,229,233,239,241,251}) == 1092889481);

}


