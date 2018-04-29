# Examples

`g++ first_example.cpp -o first_example.o`

## Creating a static library

Option -c to compile (otherwise we need a main function)
Option -d to add debug information

`g++ -c -d first_library.cpp -o first_library_file.o`

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

`g++ -c -fPIC -d first_library.cpp -o first_poi_library_file.o`

Note: Difference between -fpic and -fPIC (latter will always work but binary might be larger) Example???

`g++ -shared -Wl,-soname,libfirst_shared_so.1 -o libfirst_shared.so.1.0.0 first_poi_library_file.o`

`-Wl,-soname` sets the SONAME: should be counted up when ABI changes. The library name is the "real name".

We need to create symlink to correct name:

- `ln libfirst_shared.so.1.0.0 libfirst_shared.so.1` - necessary because when linking, SONAME is used as correct library (see below). This symlink is needed at startup time.
- `ln libfirst_shared.so.1 libfirst_shared.so` - necessary because -l looks for .so or .a files. This symlink is needed at link time.

Look at e.g. the SONAME:
`objdump -p libfirst_shared.so`

## Linking a shared library

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../first_library/ -lfirst_shared -o linked_dynamically.out`

For running, need to update LD_LIBRARY_PATH first:
`export LD_LIBRARY_PATH=/home/martin/Documents/SharedLibraries/first_library`
Also see:
`objdump -p linked_dynamically.out` contains `NEEDED libfirst_shared.so.1`

## TODO

- Windows VM...
- Hiding symbols
- More on objdump and/or readelf
- Templates and symbols