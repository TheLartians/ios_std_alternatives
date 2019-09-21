#include <doctest/doctest.h>
#include <ios_std_alternatives/variant.h>
#include <string>

using MyVariant = std::variant<int, std::string>;

TEST_CASE("get") {

  SUBCASE("get int") {
    MyVariant x = 42;

    CHECK(ios_std_alternatives::get<int>(x) == 42);
    CHECK(ios_std_alternatives::get<0>(x) == 42);
    
    CHECK_THROWS(ios_std_alternatives::get<std::string>(x));
    CHECK_THROWS(ios_std_alternatives::get<1>(x));
    CHECK_THROWS_AS(ios_std_alternatives::get<std::string>(x), ios_std_alternatives::bad_variant_access);
  }

  SUBCASE("get string") {
    MyVariant x = "test";

    CHECK(ios_std_alternatives::get<std::string>(x) == "test");
    CHECK(ios_std_alternatives::get<1>(x) == "test");
    
    CHECK_THROWS(ios_std_alternatives::get<int>(x));
    CHECK_THROWS(ios_std_alternatives::get<0>(x));
    CHECK_THROWS_AS(ios_std_alternatives::get<int>(x), ios_std_alternatives::bad_variant_access);
  }


}

TEST_CASE("visit") {
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
