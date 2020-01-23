#pragma once
#include <cstdio>
#include <exception>
#include <functional>
#include <initializer_list>
#include <list>
#include <string>
#include <utility>

namespace slu::testing {
  struct exception : std::exception {
    exception(std::string&& msg)
      : msg(std::move(msg)) {}

    virtual ~exception() override = default;

    virtual const char* what() const noexcept {
      return msg.c_str();
    }

    std::string msg;
  };

  struct testing {
    const char* name = "FIXME: NONAME";
  };

  using test = std::function<void(testing&)>;

  struct framework {
    template <typename T>
    framework(T&& tests)
      : tests(std::forward<T>(tests)) {
    }

    int run() {
      auto stat = [this]() {
        printf("[%d/%lu]", total, tests.size());
      };
      for (auto& test : tests) {
        testing t;
        try {
          test(t);
          stat();
          printf("[OK] %s\n", t.name);
          ok++;
        } catch (const std::exception& e) {
          fail++;
          stat();
          printf("[FAIL] %s: %s\n", t.name, e.what());
        } catch (...) {
          stat();
          printf("[FAIL] %s unknown error\n", t.name);
          throw;
        }
        total++;
      }
    }

    int             ok = 0, fail = 0, total = 0;
    std::list<test> tests;
  };
} // namespace slu::testing
