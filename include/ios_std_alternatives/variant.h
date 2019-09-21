#pragma once

#include <variant>
#include <exception>
#include <type_traits>
#include <functional>

namespace ios_std_alternatives {

  class bad_variant_access: public std::exception {
    const char * what() const noexcept {
      return "bad_variant_access";
    }
  };

// --- Get ---

  template <class T, typename ... Args> auto get(std::variant<Args...> & v){
    if (auto r = std::get_if<T>(&v)) {
      return *r;
    } else {
      throw bad_variant_access();
    }
  } 

  template <class T, typename ... Args> auto get(const std::variant<Args...> & v){
    if (auto r = std::get_if<T>(&v)) {
      return *r;
    } else {
      throw bad_variant_access();
    }
  } 

  template <size_t T, typename ... Args> auto get(std::variant<Args...> & v){
    if (auto r = std::get_if<T>(&v)) {
      return *r;
    } else {
      throw bad_variant_access();
    }
  } 

  template <size_t T, typename ... Args> auto get(const std::variant<Args...> & v){
    if (auto r = std::get_if<T>(&v)) {
      return *r;
    } else {
      throw bad_variant_access();
    }
  } 

// --- visit ---

  namespace detail {

    template <class F, class V, size_t Idx, typename ... Args> auto visit(F &&f, V &v) {
      if constexpr (Idx >= sizeof...(Args)) {
        throw bad_variant_access();
      } else {
        if (v.index() == Idx) {
          return std::invoke(std::forward<F>(f), ios_std_alternatives::get<Idx>(std::forward<V>(v)));
        } else {
          return detail::visit<F,std::variant<Args...>, Idx+1, Args...>(std::forward<F>(f),v);
        }
      }
    }

  }

  template <class F, typename ... Args> auto visit(F && f, std::variant<Args...> & v){
    detail::visit<F,std::variant<Args...>, 0, Args...>(std::forward<F>(f),v);
  }

  template <class F, typename ... Args> auto visit(F && f, const std::variant<Args...> & v){
    detail::visit<F,const std::variant<Args...>, 0, Args...>(std::forward<F>(f),v);
  }

}
