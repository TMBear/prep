// 1114. Print in Order: https://leetcode.com/problems/print-in-order/
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>


class Foo {
protected:
  enum class Turn {
    first = 1,
    second = 2,
    third = 3,
    allFinished = 4
  };


public:
  Foo() {
    m_currentTurn = Turn::first;
  }

  void first(std::function<void()> printFirst) {
    std::cout << "Entering first" << std::endl;
    waitForTurn(Turn::first);
    printFirst();

    m_currentTurn = Turn::second;
    m_turnCV.notify_all();
  }

  void second(std::function<void()> printSecond) {
    std::cout << "Entering second" << std::endl;
    waitForTurn(Turn::second);
    printSecond();
    
    m_currentTurn = Turn::third;
    m_turnCV.notify_all();
  }

  void third(std::function<void()> printThird) {
    std::cout << "Entering third" << std::endl;
    waitForTurn(Turn::third);
    printThird();
    
    m_currentTurn = Turn::allFinished;
    m_turnCV.notify_all();
  }

  

protected:
  void waitForTurn(Turn t) {
    std::unique_lock<std::mutex> turnLock(m_turnMutex);
    m_turnCV.wait(turnLock, [&](){return m_currentTurn == t;});
  }


  Turn m_currentTurn;
  std::mutex m_turnMutex;
  std::condition_variable m_turnCV;
};


void printFirst() {
  std::cout << "1 ";
}

void printSecond() {
  std::cout << "2 ";
}
void printThird() {
  std::cout << "3 ";
}


void test() {
  Foo foo;

  std::thread t3([&foo](){foo.third(printThird);});
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  std::thread t1([&foo](){foo.first(printFirst);});
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  std::thread t2([&foo](){foo.second(printSecond);});
  std::this_thread::sleep_for(std::chrono::milliseconds(500));



  t1.join();
  t2.join();
  t3.join();

  std::cout << std::endl;
}
