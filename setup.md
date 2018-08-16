# All examples

## Example 1: Using g++

`g++ first_example.cpp -o first_example.o`

## Example 2: Creating + linking a static library

### Creating a static library

Option -c to compile (otherwise we need a main function)
Option -g to add debug information

`g++ -c -g first_library.cpp -o first_library_file.o`

Link object files into static library

`ar -cvq libfirst.a first_library_file.o`

Use `nm libfirst.a` to have a look inside.

### Linking a static library

Linking a static library into a function.

- Even in the same folder, we need to add the path to the library
- `lib` prefix gets added automatically by `-l`

`g++ -std=c++14 -I.. linking_a_library.cpp -L../first_library/ -lfirst -o linked_statically.out`

## Example 3: Creating and Linking a Shared Library

### Creating a shared library

Need to create position independent code first (turns out to have the same size here):

`g++ -c -fPIC -g first_library.cpp -o first_poi_library_file.o`

Note: Difference between -fpic and -fPIC (latter will always work but binary might be larger) Example???

`g++ -shared -Wl,-soname,libfirst_shared.so.1 -o libfirst_shared.so.1.0.0 first_poi_library_file.o`

`-Wl,-soname` sets the SONAME: should be counted up when ABI changes. The library name is the "real name".
`-Wl,` is the prefix for linker options.

We need to create symlinks to correct name:

- `ln -s libfirst_shared.so.1.0.0 libfirst_shared.so.1` - necessary because when linking, SONAME is used as correct library (see below). This symlink is needed at startup time.
- `ln -s libfirst_shared.so.1 libfirst_shared.so` - necessary because -l looks for .so or .a files. This symlink is needed at link time.

Look at e.g. the SONAME:
`objdump -p libfirst_shared.so`

### Linking a shared library

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../first_library/ -lfirst_shared -o linked_dynamically.out`

Now see:

`objdump -p linked_dynamically.out` contains `NEEDED libfirst_shared.so.1`

However, the library is not found automatically - see `ldd linked_dynamically.out`

For running, need to update LD_LIBRARY_PATH first:
`export LD_LIBRARY_PATH=/home/martin/Documents/SharedLibraries/example3/first_library`

Alternatively (better), use the `rpath` to provide the information:
`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../first_library/ -lfirst_shared -Wl,-rpath,../first_library/ -o linked_dynamically.out`

See the "RPATH" part of `objdump -p linked_dynamicall.out`.

## Example 4: Symbol visibility in a shared library

`g++ -g -fPIC visible_library.cpp -shared -Wl,-soname,libvisible.so.1 -o libvisible.so.1.0.0`
`ln -s libvisible.so.1.0.0 libvisible.so.1`
`ln -s libvisible.so.1 libvisible.so`

Now let's look at the symbol table: (Use `objdump -t -C` instead, gives better symbols)

`objdump -t libvisible.so.1.0.0` which contains:
`ZN17my_lib_visibility9factorialEm` and `ZN17my_lib_visibility15computeNchooseKEmm`
(`-t` displays the symbol table, `-T` the dynamic symbol table)

Problem: We don't really want to export the factorial function. Now we could use it somewhere...

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../library_visibility/ -lvisible -Wl,-rpath,../library_visibility/ -o linked_dynamically_visible.out`

### Solution 1: static keyword

Static functions are not globally exported, in fact, variables only exist at file scope (C spec).
To test, add "static" keyword in `.hpp` file and recompile.
Problem: "static" has other meanings, too...

### Solution 2: visiblity

`g++ -g -fPIC -fvisibility=hidden visible_library.cpp -shared -Wl,-soname,libvisible.so.1 -o libvisible.so.1.0.0`

Now we have e.g.:

`0000000000000619 l     F .text  0000000000000031              _ZN17my_lib_visibility9factorialEm`
The second column indicates `l`, which implies that this symbol (which is a function `F`) is local, i.e. not exported.

Hence, export symbol: `__attribute__ ((visibility ("default")))`
Also: look at the size difference (e.g. 10184 with only one symbol exposed, 10352 with more symbols)

## Example 5: Symbol visibility while linking a static library in a shared library

First compile and link the static library:

`g++ -c -fPIC -g visibility_static.cpp -o visibility_static.o`
`ar -cvq libvisibilitystatic.a visibility_static.o`

Then compile  the shared library

`g++ -g -fPIC -fvisibility=hidden visible_library.cpp -shared -Wl,-soname,libvisible.so.1 -o libvisible.so.1.0.0 -Wl,--whole-archive ../library_static/libvisibilitystatic.a -Wl,--no-whole-archive`
`ln -s libvisible.so.1.0.0 libvisible.so.1`
`ln -s libvisible.so.1 libvisible.so`

The `--whole-archive` option is necessary since somewhere between gcc 3 and 4.
However, note that the factorial function is now visible in the shared library.

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../library_visibility/ -lvisible -Wl,-rpath,../library_visibility/ -o linked_dynamically_visible.out`

If we want to hide those symbols, either recompile static library, or use linker scripts.

## Example 6: Symbol visibility and classes

Set up shared library with class:

`g++ -g -fPIC shape.cpp -shared -Wl,-soname,libshape.so.1 -o libshape.so.1.0.0`
`ln -s libshape.so.1.0.0 libshape.so.1`
`ln -s libshape.so.1 libshape.so`

Linking example main:

`g++ -std=c++14 -I.. using_shape.cpp -L../shared_class/ -lshape -Wl,-rpath,../shared_class/ -o using_shape.out`

Note: We can change the implementation of the function draw. As long as we don't change the ABI, we can change everything, as the library is only loaded at startup time.

## Example 7: Symbol visibility and more complicated class setups

Set up shared library with classes:

`g++ -g -fPIC shape.cpp corner_number.cpp -shared -Wl,-soname,libshape.so.1 -o libshape.so.1.0.0`
`ln -s libshape.so.1.0.0 libshape.so.1`
`ln -s libshape.so.1 libshape.so`

Linking example main:

`g++ -std=c++14 -I.. using_shape.cpp -L../shared_class/ -lshape -Wl,-rpath,../shared_class/ -o using_shape.out`

Results in a warning, because we declared `CornerNumber` used in `Shape` as hidden.

- explicitly declare `Shape` as "default" (bad)
- compile with `fvisibility=hidden` and declare `Shape` as "default" and don't declare `CornerNumber` as hidden (bad)
- Forward declare your class `Shape`
- Expose only the function symbols

But everything works, so where is the problem?

The "= default" in `shape.cpp` is not very nice, let's just put it in the header. Compile and link, we get an error:

`Warning: undefined reference to »shape_lib::CornerNumber::~CornerNumber()«`

- compiler needs symbol definition to generate functions - in this case, the generated compiler needs to call the destructor of CornerNumber. This information is hidden, hence the previous warning
- the first two "fixes" above don't actually change anything
- only forwarding works: then the compiler actually never inlines, so the information is not necessary

## Example 8: Exposing function symbols instead of classes

Compile, link and use:
`g++ -g -fPIC shape.cpp corner_number.cpp -shared -Wl,-soname,libshape.so.1 -o libshape.so.1.0.0`
`ln -s libshape.so.1.0.0 libshape.so.1`
`ln -s libshape.so.1 libshape.so`
`g++ -std=c++14 -I.. using_shape.cpp -L../shared_class/ -lshape -Wl,-rpath,../shared_class/ -o using_shape.out`

Works. But use a derived class:

`g++ -std=c++14 -I.. using_square.cpp square.cpp -L../shared_class/ -lshape -Wl,-rpath,../shared_class/ -o using_square.out`

We get an error:

`Warning: undefined reference to »typeinfo for shape_lib::Shape«`

The warning is pretty good and tells us (for instance) that he pretty obviously seems to be really missing some typeinfo:

`Warning: »shape_lib::Square« with higher visibility than the type of its field »shape_lib::Square::<anonym>«`

## Example 9: Inline function visibility

Code example derived from example given by user Ivan in:

<https://stackoverflow.com/questions/48621251/why-fvisibility-inlines-hidden-is-not-the-default>

### Global visibility of everything

If we compile the library (don't forget `ln -s libshared.so.1.0.0 libshared.so.1` and `ln -s libshared.so.1 libshared.so`):

`g++ -g -fPIC shared.cpp -shared -Wl,-soname,libshared.so.1 -o libshared.so.1.0.0`
`g++ -g -I. main.cpp -L. -lshared -Wl,-rpath,. -o try.out`

we get the following behaviour: static local and function pointers are identical:

shared() - static local 0x55b118b77031
shared() - function ptr 0x55b1189767c2
main() - static local 0x55b118b77031
main() - function ptr 0x55b1189767c2

we also get two symbols (a weak and a unique global) when looking at symbols:

`objdump -T -C libshared.so | grep "foo"`
0000000000201029 u    DO .bss   0000000000000001  Base        foo()::a
0000000000000701  w   DF .text  000000000000000d  Base        foo()

### Inline Functions hidden

If we compile using the "-fvisiblity-inlines-hidden" flag  (don't forget `ln -s libshared.so.1.0.0 libshared.so.1` and `ln -s libshared.so.1 libshared.so`):

`g++ -g -fPIC -fvisibility-inlines-hidden shared.cpp -shared -Wl,-soname,libshared.so.1 -o libshared.so.1.0.0`
`g++ -g -I. main.cpp -L. -lshared -Wl,-rpath,. -o try.out`

we get the following behaviour: static local pointers are identical, but function pointers are not:

shared() - static local 0x55a115b27031
shared() - function ptr 0x7f795d5406ae
main() - static local 0x55a115b27031
main() - function ptr 0x55a1159267a2

we also get only one symbol (the unique global) when looking at it:

`objdump -T -C libshared.so | grep "foo"`
0000000000201029 u    DO .bss   0000000000000001  Base        foo()::a

In principle, this is NOT standard compliant!

### Completely hidden functions

If we compile using both "-fvisiblity-inlines-hidden" and "-fvisibility="hidden"" flag  (don't forget `ln -s libshared.so.1.0.0 libshared.so.1` and `ln -s libshared.so.1 libshared.so`):

`g++ -g -fPIC -fvisibility="hidden" -fvisibility-inlines-hidden shared.cpp -shared -Wl,-soname,libshared.so.1 -o libshared.so.1.0.0`
`g++ -g -I. main.cpp -L. -lshared -Wl,-rpath,. -o try.out`

we get the following behaviour: the main function just doesn't know about the other library's function, all pointers are different:

shared() - static local 0x7f8320c84029
shared() - function ptr 0x7f8320a8366e
main() - static local 0x55be67230031
main() - function ptr 0x55be6702f772

we also have no exported symbol for `foo`.

For class member functions and header files, if we manually export the method symbol in `shared.cpp`, we should get the behaviour as when using only the "-fvisibility-inlines-hidden" flag - here, we get the first behaviour.

## Example 10: Templates

## Example 11: Dynamically loading library

## TODO

- Windows VM...
- More on objdump, nm and readelf
- How does -fvisibility-inlines-hidden work?
