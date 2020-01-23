#pragma once
#include <tuple>
#include <type_traits>
#include <utility>

namespace slu::waterfall {
  struct end {
  };

  namespace details {
    namespace lambda_ext {
      template <typename Ret, typename Cls, typename IsMutable, typename... Args>
      struct types {
        template <size_t i>
        struct arg {
          typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
      };

      template <typename Ld>
      struct lambda_type : lambda_type<decltype(&Ld::operator())> {
      };

      template <typename Ret, typename Cls, typename... Args>
      struct lambda_type<Ret (Cls::*)(Args...)>
        : types<Ret, Cls, std::true_type, Args...> {
      };

      template <typename Ret, typename Cls, typename... Args>
      struct lambda_type<Ret (Cls::*)(Args...) const>
        : types<Ret, Cls, std::false_type, Args...> {
      };
    } // namespace lambda_ext

    template <typename Err, typename T1, typename... T>
    void
    run_last(Err err, T1 func, end, T...) {
      typedef typename lambda_ext::lambda_type<decltype(func)>::template arg<1>::type Res;
      func(err, Res{});
    }

    template <typename Err, typename T1, typename... T>
    void
    run_last(Err err, T1 func, T... rest) {
      run_last(std::move(err), rest...);
    }

    template <typename Err, typename T0, typename T1, typename... T>
    void
    run_internal(Err err, T0 res, T1 func, end, T...) {
      func(err, res);
    }

    template <typename Err, typename T0, typename T1, typename... T>
    void run_internal(Err err, T0 res, T1 func, T... rest) {
      if (err == nullptr) {
        func(res, [&](Err err, auto nextResult) {
          run_internal(std::move(err),
                       std::move(nextResult),
                       rest...);
        });
      } else {
        run_last(std::move(err), rest...);
      }
    }

    template <typename Err, typename TStartVal>
    struct created {
      Err       err;
      TStartVal startVal;

      template <typename... T>
      void run(T... args) {
        details::run_internal<Err, TStartVal, T...>(std::move(err),
                                                    std::move(startVal),
                                                    args...,
                                                    waterfall::end{});
      }
    };
  } // namespace details

  template <typename Err, typename TStartVal>
  details::created<Err, TStartVal> create(Err err, TStartVal startVal) {
    return {std::move(err), std::move(startVal)};
  }
} // namespace slu::waterfall