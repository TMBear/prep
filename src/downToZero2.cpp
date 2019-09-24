//////////////////////////////////////////////////////////////////////////////////////////////////////
// https://www.hackerrank.com/challenges/down-to-zero-ii/problem
//
#include <iostream>
#include <vector>


class DownZero {
  const int c_maxVal;

public:
  DownZero(const std::size_t maxVal);

  void initialize();

  std::size_t getSteps(std::size_t val);


private:
  void tryNewStep(const std::size_t indx, const std::size_t steps);
  void tryMul(const std::size_t i);
  void tryAdd(const std::size_t i);

private:
  std::vector<std::size_t> m_steps;

};

DownZero::DownZero(const std::size_t maxVal)
  : c_maxVal(maxVal)
{}


void DownZero::initialize() {
  m_steps.resize(c_maxVal);
  std::fill(m_steps.begin(), m_steps.end(), c_maxVal);
  m_steps[0] = 0;

  for (std::size_t i = 0; i < c_maxVal; ++i) {
    tryMul(i);
    tryAdd(i);
  }
}





void DownZero::tryAdd(std::size_t i) {
  tryNewStep(i + 1, m_steps[i] + 1);
}


void DownZero::tryMul(std::size_t i) {
  if (i == 0)
    return;

  const auto nextStep = m_steps[i] + 1;
  const auto maxMul = std::min(i, c_maxVal / i);

  for (std::size_t mul = 1; mul <= maxMul; mul++) {
    tryNewStep(mul * i, nextStep);
  }
}


void DownZero::tryNewStep(const std::size_t indx, const std::size_t steps){
  if (indx >= m_steps.size())
    return;

  m_steps[indx] = std::min(m_steps[indx], steps);
}


std::size_t DownZero::getSteps(std::size_t val) {
  if (val >= m_steps.size())
    return std::numeric_limits<std::size_t>::max();

  return m_steps[val];
}





void downToZero2() {
  const std::size_t maxVal = 1000001;
  DownZero dz(maxVal);
  dz.initialize();

  std::cout << dz.getSteps(94) << std::endl;
}

