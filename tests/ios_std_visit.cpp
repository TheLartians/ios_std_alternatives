#include <doctest/doctest.h>
#include <ios_std_alternatives/variant.h>
#include <string>

TEST_CASE("visit") {
  using MyVariant = std::variant<std::string, int>;
  bool visited = false;

  SUBCASE("visit int") {
    MyVariant x = 42;
    ios_std_alternatives::visit([&](auto && v){
      if constexpr (std::is_same<typename std::decay<decltype(v)>::type, int>::value) {
        visited = true;
        CHECK(v == 42);
      } else {
        CHECK(false);
      }
    }, x);
    CHECK(visited);
  }

  SUBCASE("visit string") {
    MyVariant x = "test";
    ios_std_alternatives::visit([&](auto && v){
      if constexpr (std::is_same<typename std::decay<decltype(v)>::type, std::string>::value) {
        visited = true;
        CHECK(v == "test");
      } else {
        CHECK(false);
      }
    }, x);
    CHECK(visited);
  }

}
