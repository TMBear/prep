#include <iostream>
#include <vector>
#include <numeric>


namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
};




template<typename Container>
class ValStack {
public:
  ValStack(const Container& data) 
    : m_data(std::move(data))
    , m_curTop(m_data.begin())
    , m_consumed(0)
  {}

  // Try to consume another value. Returns value consumed or -1 if not possible (end of stack)
  int consume();
  // Consume 0 or more values but with their sum not to exceed max. Returns total value consumed.
  int consumeUpTo(int max);
  // Puts a value back to stack, returns its value or -1 if not possible (top of the stack)
  int unconsume();
  // Returns the number of consumed values.
  int getValuesConsumed() const;

  void print(std::ostream& out) const;

private:
  Container m_data;
  typename Container::const_iterator m_curTop;
  typename Container::value_type m_consumed;

};


template<typename Container>
int ValStack<Container>::consume() {
  if (m_curTop == m_data.end())
    return -1;
  int val = *m_curTop;
  ++m_curTop;
  return val;
}




template<typename Container>
int ValStack<Container>::unconsume() {
  if (m_curTop == m_data.begin())
    return -1;
  --m_curTop;
  return *m_curTop;
}



template<typename Container>
int ValStack<Container>::consumeUpTo(int max) {
  int totalConsumed = 0;
  int curCons = 0;
  while ((curCons = consume()) != -1) {
    if (totalConsumed + curCons > max) {
      unconsume();
      break;
    }

    totalConsumed += curCons;
  }

  return totalConsumed;
}


template<typename Container>
int ValStack<Container>::getValuesConsumed() const {
  return m_curTop - m_data.begin();
}



template<typename Container>
void ValStack<Container>::print(std::ostream& out) const {
  out << Color::Modifier(Color::FG_RED);
  for (auto it = m_data.begin(); it != m_curTop; ++it)
    out << *it << " ";

  std::cout << Color::Modifier(Color::FG_DEFAULT);
  for (auto it = m_curTop; it != m_data.end(); ++it)
    out << *it << " ";

  out << "   #cons: " << getValuesConsumed() << " ValCons: ";
  out << std::accumulate(m_data.begin(), m_curTop, 0);
}


template <typename Container>
std::ostream& operator<<(std::ostream& out, const ValStack<Container>& st) {
  st.print(out);
  return out;
}




int twoStacks(int max, const std::vector<int>& a, const std::vector<int>& b) {
  ValStack<std::vector<int>> s1(a);
  ValStack<std::vector<int>> s2(b);

  max -= s1.consumeUpTo(max);
  max -= s2.consumeUpTo(max);

  int valuesConsumedMax = s1.getValuesConsumed() + s2.getValuesConsumed();

//  std::cout << "maxRem: " << max << " totalValCons: " << valuesConsumedMax << std::endl;
//  std::cout << s1 << std::endl;
//  std::cout << s2 << std::endl;
//  std::cout << std::endl;

  while (true) {
    int extraVal = s1.unconsume();
    if (extraVal < 0) // s1 is empty
      break;

    max += extraVal;
    max -= s2.consumeUpTo(max);

    valuesConsumedMax = std::max(valuesConsumedMax, s1.getValuesConsumed() + s2.getValuesConsumed());

    
//    std::cout << "maxRem: " << max << " totalValCons: " << valuesConsumedMax << std::endl;
//    std::cout << s1 << std::endl;
//    std::cout << s2 << std::endl;
//    std::cout << std::endl;
  }

  return valuesConsumedMax;

}



void gameOfTwoStacks () {
  std::cout << "Hello World!" << std::endl;
  {
    std::vector<int> a = {4, 2, 4, 6, 1};
    std::vector<int> b = {2, 1, 8, 5};

    std::cout << twoStacks(10, a, b) << std::endl;
  }

  return 0;
}


