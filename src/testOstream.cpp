#include "testOstream.h" 

TestOstream::TestOstream(bool enable)
  : m_enabled(enable)
  , m_printIdent(true)
  , m_baseOstream(std::cout)
{}


void TestOstream::incIndent() {
  m_identSize += 2;
}


void TestOstream::decIndent() {
  m_identSize -= 2;
}


std::ostream& TestOstream::getBaseOstream() {
  return m_baseOstream;
}


bool TestOstream::isEnabled() {
  return m_enabled;
}


bool& TestOstream::shouldPrintIdent() {
  return m_printIdent;
}


std::size_t TestOstream::getIdentSize() {
  return m_identSize;
}


TestOstream& operator<<(TestOstream& out, ostream_manipulator pf) {
  if (!out.isEnabled())
    return out;
  out.shouldPrintIdent() = true;
  pf(std::cout);
  return out;
}


TestStreamIdenter::TestStreamIdenter(TestOstream& out)
  : m_stream(out)
{
  m_stream.incIndent();  
}

TestStreamIdenter::~TestStreamIdenter() {
  m_stream.decIndent();
}
