#include <cstdio>

struct A { };

inline A & foo()
{
    static A a;
    return a;
}

static __attribute__((constructor)) void init()
{
    auto p = &foo();
    std::printf("shared() - static local %p\n", p);
    std::printf("shared() - function ptr %p\n", &foo);
}