# Libraries and versioning

## Example 1: SONAME versioning

This has already been done in other examples. In principle, just compile 

`g++ -std=c++14 -g -c -fPIC first_library.cpp -o first_poi_library_file.o`
`g++ -shared -Wl,-soname,libfirst_shared.so.2 -o libfirst_shared.so.2.0.0 first_poi_library_file`
`ln -s libfirst_shared.so.2.0.0 libfirst_shared.so.2`
`ln -s libfirst_shared.so.2 libfirst_shared.so`

and then compile the example 

`g++ -std=c++14 -I.. linking_a_shared_library.cpp -L../first_library/ -lfirst_shared -Wl,-rpath,../first_library/ -o linked_dynamically.out`

Changing the version, i.e. `libfirst_shared.so.2.5.4` doesn't matter.
Changing the SONAME (to e.g.  `libfirst_shared.so.3`) produces

`./linked_dynamically.out: error while loading shared libraries: libfirst_shared.so.2: cannot open shared object file: No such file or directory`

It is possible to replace the needed so-file, but this is rarely a good idea
`patchelf --replace-needed libfirst_shared.so.2 libfirst_shared.so.3 linked_dynamicall.out`