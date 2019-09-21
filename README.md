# ios_std_alternatives

C++17 is awesome, however some features, such as `std::get` are [only available for recent iOS versions](https://stackoverflow.com/questions/52310835/xcode-10-call-to-unavailable-function-stdvisit/53868971).
This project adds some workaround methods to target older iOS versions.
Note that it is currently only implemented for my personal use-cases and no guarantees are given to completeness or standard compliance.

## Run tests

```
cmake -H. -Bbuild -Dios_std_alternatives_TESTS_ENABLE_TESTS=On
cmake --build build -j8
./build/tests/ios_std_alternatives_test
```

## Test if the tests compile for for iOS 9.0

```
cmake -E env CXXFLAGS="-fno-aligned-allocation" cmake -H. -Bbuild-ios -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_DEPLOYMENT_TARGET=9.0 "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64;" -DCMAKE_IOS_INSTALL_COMBINED=YES -Dios_std_alternatives_TESTS_ENABLE_TESTS=On
cmake --build build-ios -j8
```
