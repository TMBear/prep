#include <iostream>
#include <iomanip>


class TestOstream  {
public:
  TestOstream(bool enable);

  void incIndent();
  void decIndent();

  std::ostream& getBaseOstream();

  bool isEnabled();
  bool& shouldPrintIdent();

  std::size_t getIdentSize();

private:
  bool m_enabled;
  bool m_printIdent;
  std::size_t m_identSize;

  std::ostream& m_baseOstream;
};


struct TestStreamIdenter {
  TestStreamIdenter(TestOstream& out);
  ~TestStreamIdenter();

private:
  TestOstream& m_stream;
};


typedef std::ostream& (*ostream_manipulator)(std::ostream&);
TestOstream& operator<<(TestOstream& os, ostream_manipulator pf);

template<class T>
TestOstream& operator<<(TestOstream& out, const T& val) {
  if (!out.isEnabled())
    return out;

  if (out.shouldPrintIdent()) {
    out.shouldPrintIdent() = false;
    if (out.getIdentSize() >= 2)
      out.getBaseOstream() << std::string(out.getIdentSize() - 2, ' ');
  }
  
  out.getBaseOstream() << val;
  return out;
}
