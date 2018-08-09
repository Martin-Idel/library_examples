# Libraries and linking

## Example 1: Using g++

`g++ first_example.cpp -o first_example.o`

Have a look via `readelf -a` (objdump needs several different actions)

## Example 2: Creating + linking a static library

### Creating a static library

Option -c to compile (otherwise we need a main function)
Option -g to add debug information

`g++ -std=c++14 -g -c first_library.cpp -o first_library_file.o`

Link object files into static library

`ar -cvq libfirst.a first_library_file.o`

Use `objdump -a libfirst.a` to have a look at which object files are in there and/or `readelf -a libfirst.a` to see everything.

### Linking a static library

Linking a static library into a function.

- Even in the same folder, we need to add the path to the library
- `lib` prefix gets added automatically by `-l`

`g++ -std=c++14 -I.. linking_a_library.cpp -L../first_library/ -lfirst -o linked_statically.out`

## Example 3: Creating and Linking a Shared Library

### Creating a shared library

Need to create position independent code first (turns out to have the same size here):

`g++ -std=c++14 -g -c -fPIC first_library.cpp -o first_poi_library_file.o`

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

## Example 4: Dynamic lib

############################################################## TODO