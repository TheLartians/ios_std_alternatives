[![Actions Status](https://github.com/TheLartians/ios_std_alternatives/workflows/Test%20Mac/badge.svg)](https://github.com/TheLartians/ios_std_alternatives/actions)
[![Actions Status](https://github.com/TheLartians/ios_std_alternatives/workflows/Test%20iOS/badge.svg)](https://github.com/TheLartians/ios_std_alternatives/actions)
[![Actions Status](https://github.com/TheLartians/ios_std_alternatives/workflows/Test%20Linux/badge.svg)](https://github.com/TheLartians/ios_std_alternatives/actions)

# ios_std_alternatives

C++17 is awesome, however some features, such as `std::get` are [only available for recent iOS versions](https://stackoverflow.com/questions/52310835/xcode-10-call-to-unavailable-function-stdvisit/53868971).
This project adds alternative implementations to broken iOS types.

## Run tests

```bash
cmake -H. -Bbuild -Dios_std_alternatives_ENABLE_TESTS=On
cmake --build build -j8
./build/tests/ios_std_alternatives_test
```

## Compile tests for iOS 9.0

```bash
cmake -E env CXXFLAGS="-fno-aligned-allocation" cmake -H. -Bbuild-ios -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_DEPLOYMENT_TARGET=9.0 -DCMAKE_INSTALL_PREFIX=./build-ios/root -DCMAKE_IOS_INSTALL_COMBINED=YES -Dios_std_alternatives_ENABLE_TESTS=On
cmake --build build-ios --target install -j8
```
