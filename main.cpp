#include "Function.h"

#include <cassert>
#include <iostream>

int globalAdd(int a, int b)
{
    return a + b;
}

struct Add
{
    int operator()(int a, int b) const
    {
        return a + b;
    }
    int constF(int a, int b) const
    {
        return a + b;
    }
    int mutableF(int a, int b)
    {
        return a + b;
    }
    int data = 65;
};

int main()
{
    using namespace vehlwn;
    {
        Function<int(int, int)> f = globalAdd;
        assert((f(3, 0) == 3));
    }
    {
        Function<int(int, int)> f = [](auto a, auto b) { return a + b; };
        assert((f(3, 1) == 4));
    }
    {
        Add obj;
        Function<int(int, int)> f = obj;
        assert((f(3, 2) == 5));
    }
    {
        const Add obj;
        Function<int(const Add&, int, int)> f = &Add::constF;
        // f = &Add::mutableF won't compile and raise obscure error like std::invoke:
        // no matching overloaded function found. That's why I put static assert in
        // template constructor.
        assert((f(obj, 3, 3) == 6));
    }
    {
        const Add obj;
        Function<int(const Add&, int, int)> f = &Add::operator();
        assert((f(obj, 3, 4) == 7));
    }
    {
        Add obj;
        Function<int(Add&, int, int)> f = &Add::constF;
        assert((f(obj, 3, 5) == 8));
    }
    {
        Add obj;
        Function<int(Add&, int, int)> f = &Add::mutableF;
        assert((f(obj, 3, 6) == 9));
    }
    {
        Add obj;
        Function<int(Add&)> f = &Add::data;
        assert((f(obj) == 65));
    }
}
