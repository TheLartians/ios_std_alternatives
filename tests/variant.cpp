#include <doctest/doctest.h>
#include <ios_std_alternatives/variant.h>
#include <variant>
#include <string>

using MyVariant = isa::variant<int, std::string>;

TEST_CASE("get") {

  SUBCASE("get int") {
    MyVariant x = 42;

    CHECK(isa::get<int>(x) == 42);
    CHECK(isa::get<0>(x) == 42);
    
    CHECK_THROWS(isa::get<std::string>(x));
    CHECK_THROWS(isa::get<1>(x));
    CHECK_THROWS_AS(isa::get<std::string>(x), mpark::bad_variant_access);
  }

  SUBCASE("get string") {
    MyVariant x = "test";

    auto &ref = isa::get<std::string>(x);
    CHECK(ref == "test");
    CHECK(isa::get<1>(x) == "test");
    
    CHECK_THROWS(isa::get<int>(x));
    CHECK_THROWS(isa::get<0>(x));
    CHECK_THROWS_AS(isa::get<int>(x), mpark::bad_variant_access);
  }


}

TEST_CASE("visit") {
  bool visited = false;

  SUBCASE("visit int") {
    MyVariant x = 42;
    isa::visit([&](auto & v){
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
    isa::visit([&](auto & v){
      if constexpr (std::is_same<typename std::decay<decltype(v)>::type, std::string>::value) {
        visited = true;
        CHECK(v == "test");
      } else {
        CHECK(false);
      }
    }, x);
    CHECK(visited);
  }

  SUBCASE("return reference") {
    MyVariant x = 42;

    int &y = isa::visit([](auto & v) -> int & {
      if constexpr (std::is_same<typename std::decay<decltype(v)>::type, int>::value) {
        return v;
      } else {
        throw "unexpected type";
      }
    }, x);  

    CHECK(&y == &isa::get<int>(x));
  }

}
