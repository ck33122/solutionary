// https://leetcode.com/problems/print-in-order/submissions/

#include <functional>
#include <future>
using namespace std;

// first variant (slower one)

class Foo {
public:
  promise<bool> p1;
  promise<bool> p2;

  Foo() = default;

  void first(function<void()> printFirst) {
    printFirst();
    p1.set_value(true);
  }

  void second(function<void()> printSecond) {
    p1.get_future().wait();
    printSecond();
    p2.set_value(true);
  }

  void third(function<void()> printThird) {
    p2.get_future().wait();
    printThird();
  }
};

// second variant (the fastest)

class Foo {
public:
  mutex p1;
  mutex p2;

  Foo() {
    p1.lock();
    p2.lock();
  }

  void first(function<void()> printFirst) {
    printFirst();
    p1.unlock();
  }

  void second(function<void()> printSecond) {
    auto u = unique_lock<mutex>(p1);
    printSecond();
    p2.unlock();
  }

  void third(function<void()> printThird) {
    auto u = unique_lock<mutex>(p2);
    printThird();
  }
};

// third and fourth are quite similar and uses atomics.
// atomics were too slow for that problem
