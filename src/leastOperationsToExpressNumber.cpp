// 964. Least Operators to Express Number - https://leetcode.com/problems/least-operators-to-express-number/
#include <iostream>
#include <vector>
#include <unordered_map>
#include "testOstream.h"

const int c_maxOps = 1000000;

using ValType = long long;

struct Step {
  ValType target;
  ValType ops;
};

bool operator<(const Step& lhs, const Step& rhs) {
  return lhs.ops < rhs.ops;
}

std::ostream& operator<<(std::ostream& out, const Step& s) {
  out << "(" << s.ops << ", " << s.target << ")";
  return out;
}


class StepsContainer {
  public:
  void insertStep(const Step& s) {
    ValType ops = s.ops;
    ValType target = std::abs(s.target);

    if (m_steps.find(target) != m_steps.end())
      ops = std::min(ops, m_steps[target]);

    m_steps[target] = ops;
  }

  Step extractStepWithLowestOps() {
    Step result{0, c_maxOps};
    if (empty())
      return result;

    for (const auto& s : m_steps) {
      if (s.second < result.ops) {
        result.ops = s.second;
        result.target = s.first;
      }
    }

    m_steps.erase(result.target);
    return result;
  }

  bool empty() const {
    return m_steps.empty();
  }

private:
  // Container for target->ops
  std::unordered_map<ValType, ValType> m_steps;
};



class Solution {
public:
  int leastOpsExpressTarget(int x, int target) {
    StepsContainer steps;
    steps.insertStep({target, -1}); // -1 for the initail stae (0 + expression), -1 to compensate for "+")

    while (!steps.empty()) {
      const auto curStep = steps.extractStepWithLowestOps();

      if (curStep.target == 0)
        return curStep.ops;

      const auto newSteps = getPossibleSteps(x, curStep);
      for (const auto& s : newSteps)
        steps.insertStep(s);
    }

    return -1;
  }

private:

  std::vector<Step> getPossibleSteps(int x, const Step& curStep) {
    if (curStep.target == 0)
      return {curStep};

    if (curStep.target == x)
      return {{0, curStep.ops + 1}};

    if (curStep.target < x) {
      int fwdSteps = curStep.target * 2;  // target -x/x -x/x ... -x/x
      int inverseSteps = (x - curStep.target) * 2 + 1;  // target - x +x/x +x/x ... +x/x

      int minOps = std::min(fwdSteps, inverseSteps);
      return {{0, curStep.ops + minOps}};
    }

    std::vector<Step> result;
    // 2 ways = advance one step forward (maximum to some power of x) or jump over target and then later advance backward.
    ValType pow =  0;
    ValType advance = 0;

    maxPow(x, curStep.target, pow, advance);

    result.push_back({curStep.target - advance, curStep.ops + pow});
    result.push_back({curStep.target - advance * x, curStep.ops + pow + 1});


    return result;
  }


  void maxPow(const ValType base, const ValType target, ValType& p, ValType& res) {
    res = 1;
    p = -1;
    ValType nextRes = 1;
    while (nextRes < target) {
      res = nextRes;
      ++p;
      nextRes *= base;
    }
  }
};



static void test() {
  Solution s;
  std::cout << s.leastOpsExpressTarget(100, 200000000) << std::endl;


  assert(s.leastOpsExpressTarget(3, 19) == 5);
  assert(s.leastOpsExpressTarget(5, 501) == 8);
  assert(s.leastOpsExpressTarget(100, 100000000) == 3);
  assert(s.leastOpsExpressTarget(2, 125046) == 50);
  assert(s.leastOpsExpressTarget(3, 365) == 17);
  assert(s.leastOpsExpressTarget(11, 551302) == 60);

}



