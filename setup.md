# Examples

`g++ first_example.cpp -o first_example.o`

## Creating a static library

Option -c to compile (otherwise we need a main function)
Option -g to add debug information

`g++ -c -g first_library.cpp -o first_library_file.o`

Link object files into static library

`ar -cvq libfirst.a first_library_file.o`

## Linking a static library

Linking a static library into a function.

- Even in the same folder, we need to add the path to the library
- `lib` prefix gets added automatically by `-l`

`g++ -std=c++14 linking_a_library.cpp -L./ -lfirst` (old folder structure)
`g++ -std=c++14 -I.. linking_a_library.cpp -L../first_library/ -lfirst -o linked_statically.out`

## Creating a shared library

Need to create position independent code first (turns out to have the same size here):

`g++ -c -fPIC -g first_library.cpp -o first_poi_library_file.o`

Note: Difference between -fpic and -fPIC (latter will always work but binary might be larger) Example???

`g++ -shared -Wl,-soname,libfirst_shared_so.1 -o libfirst_shared.so.1.0.0 first_poi_library_file.o`

`-Wl,-soname` sets the SONAME: should be counted up when ABI changes. The library name is the "real name".

We need to create symlinks to correct name:

- `ln -s libfirst_shared.so.1.0.0 libfirst_shared.so.1` - necessary because when linking, SONAME is used as correct library (see below). This symlink is needed at startup time.
- `ln -s libfirst_shared.so.1 libfirst_shared.so` - necessary because -l looks for .so or .a files. This symlink is needed at link time.

Look at e.g. the SONAME:
`objdump -p libfirst_shared.so`

## Linking a shared library

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../first_library/ -lfirst_shared -o linked_dynamically.out`

For running, need to update LD_LIBRARY_PATH first:
`export LD_LIBRARY_PATH=/home/martin/Documents/SharedLibraries/first_library`
Also see:
`objdump -p linked_dynamically.out` contains `NEEDED libfirst_shared.so.1`
(`-p` displays information from the ELF header)

## Symbol visiblity

`g++ -g -fPIC visible_library.cpp -shared -Wl,-soname,libvisible.so.1 -o libvisible.so.1.0.0`
`ln -s libvisible.so.1.0.0 libvisible.so.1`
`ln -s libvisible.so.1 libvisible.so`

Now let's look at the symbol table:

`objdump -t libvisible.so.1.0.0` which contains:
`ZN17my_lib_visibility9factorialEm` and `ZN17my_lib_visibility15computeNchooseKEmm`
(`-t` displays the symbol table, `-T` the dynamic symbol table)

Problem: We don't really want to export the factorial function. Now we could use it somewhere...

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../library_visibility/ -lvisible -o linked_dynamically_visible.out`
`export LD_LIBRARY_PATH=/home/martin/Documents/SharedLibraries/library_visibility`

The linking should have gone wrong if we want to hide our factorial implementation:

`g++ -g -fPIC -fvisibility=hidden visible_library.cpp -shared -Wl,-soname,libvisible.so.1 -o libvisible.so.1.0.0`

Now we have e.g.:

`0000000000000619 l     F .text  0000000000000031              _ZN17my_lib_visibility9factorialEm`
The second column indicates `l`, which implies that this symbol (which is a function `F`) is local, i.e. not exported.

Hence, export symbol: `__attribute__ ((visibility ("default")))`
Also: look at the size difference (e.g. 10184 with only one symbol exposed, 10352 with more symbols)

## TODO

- Windows VM...
- More on objdump and/or readelf
- Templates and symbols