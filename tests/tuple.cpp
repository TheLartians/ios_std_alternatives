#include <doctest/doctest.h>

#include <string>
#include <tuple>

#include <ios_std_alternatives/variant.h>

TEST_CASE("get") {

  std::tuple<int,std::string> v = std::make_tuple(42, "test");
  CHECK(std::get<0>(v) == 42);
  CHECK(std::get<1>(v) == "test");

}
