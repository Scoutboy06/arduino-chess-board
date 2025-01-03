#pragma once

#ifdef ARDUINO

#define PRINT(x) Serial.print(x)

#else

#include <bitset>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>

#define PRINT(x) std::cout << x

#endif
