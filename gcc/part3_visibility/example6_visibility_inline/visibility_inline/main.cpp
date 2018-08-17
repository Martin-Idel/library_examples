#include <cstdio>

struct A { };

inline A & foo()
{
    static A a;
    return a;
}

int main()
{
    auto p = &foo();
    std::printf("main() - static local %p\n", p);
    std::printf("main() - function ptr %p\n", &foo);
}