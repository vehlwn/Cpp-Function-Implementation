# Cpp-Function-Implementation

Demonstrates possible implementation of [std::function](https://en.cppreference.com/w/cpp/utility/functional/function).

Supports global functions, class objects with operator() and pointers to member functions.

Example:
```C++
#include "VariadicScanf.h"

#include <cassert>
#include <iostream>

int main()
{
    int n = 1111;
    int b = 2222;
    std::cout << "2 input, 2 format, 2 arguments..." << std::endl;
    int ret = vehlwn::variadicSscanf("be 42 iu 69 rt", "be % iu % rt", n, b);
    assert(ret == 2);
    assert(n == 42);
    assert(b == 69);
}
```
