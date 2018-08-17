# Libraries and linking

## Example 1: Using MSVC++

`cl /EHsc first_example.cpp`

Inspect via 

`dumpbin /ALL first_example.exe` (Attention: the data section is... long)
`dumpbin /IMPORT first_example.exe` (Import section only)

## Example 2: Creating + linking a static library

### Creating a static library

Option /c to compile (otherwise we need a main function)
Option /EHsc to make it a bit smaller (exception wrapping code)

`cl /EHsc /c first_library.cpp /Fofirst_library_file.obj`

Link object files into static library

`lib first_library_file.obj`

Have a look at the files and see public symbols:

`dumpbin /ALL first_library.lib`

### Linking a static library

Linking a static library into a function:

`cl /EHsc linking_a_library.cpp /I ..\ /link ..\first_library\first_library.lib`

## Example 3: Creating and Linking a Shared Library

### Creating a shared library

Same as before:
`cl /EHsc /c first_library.cpp /Fofirst_library_file.obj`

Link into dynamic library:

`link /DLL /out:first_dynamic_library.dll first_library_file.obj`

or in short, use the `/LD` flag:

`cl /EHsc /LD first_library.cpp /link /out:first_dynamic_library.dll`

Note: When we defined `__declspec( dllexport )`, then apart from the `.dll` file, we also get a `.lib` file and a `.exp` file. The latter is needed for circular dependencies.

### Linking a shared library

As before:

`cl /EHsc linking_a_shared_library.cpp /I ..\ /link ..\first_library\first_library.lib`

Problem: The dll is not in the path. There are no very nice solutions:

- Put all libraries in the same folder as the executable (only the `.dll` files)
- Add to PATH variable

Note: you cannot link against a `.dll`, you have to link against a `.lib` file. If none exists, the however, probably `__declspec( dllexport )` are missing.

## Example 4: Dynamic lib

Compile shared library
`cl /EHsc /LD first_library.cpp /link /out:first_dynamic_library.dll`

Load dynamically
`cl /EHsc dynamic_loading.cpp /I ..\`

Note: you can only open symbols also exported via `__declspec( dllexport )`.

## Example 5: Creating .lib from .dll only

Only object: `first_dynamic_library.dll`.

Read symbols: `dumpbin /exports first_dynamic_library.dll`.
Write symbol names into `first_library.def` with `EXPORTS` header.
Then run: `lib /def:first_library.def /out:first_library.lib` to create `.exp` and `.lib` files.

Linking works as before (idea from <https://adrianhenke.wordpress.com/2008/12/05/create-lib-file-from-dll/>)