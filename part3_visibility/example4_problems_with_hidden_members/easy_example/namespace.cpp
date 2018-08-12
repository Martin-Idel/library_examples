class __attribute__ ((visibility ("hidden"))) Foo {
public:
  void bar() {}
};

class Bar {
public:
  Foo foo;
};

int main() {}