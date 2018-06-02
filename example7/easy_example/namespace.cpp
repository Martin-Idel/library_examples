class __attribute__ ((visibility ("hidden"))) Foo {
public:
  void bar() {}
};

class __attribute__ ((visibility ("default"))) Bar {
public:
  Foo foo;
};

int main() {}