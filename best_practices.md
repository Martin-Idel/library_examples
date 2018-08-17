# Best Practices on Linux

## Building

- Use the rpath of a `.so` instead of relying on the `LD_LIBRARY_PATH`.
- Always build with `-fPIC` option, as shared libraries need it.
- `-fpic` provides better performance, but it is less general than `-fPIC` - it can only work for small libraries.
- When dynamically loading library functions, export the functions via `extern "C"`. When loading classes, provide constructor and deletion factories to circumvent issues with `new` and `delete` overloads.

## Versioning

- Use soname versioning for "real" libraries. If library changes fast, this is probably not very good
- Increase SONAME version when ABI changes, i.e. `mylib.so.1`
- Format or "real name" is not fixed. In glibc it is "current, revision, age", where "age" reflects backwards compatibility.
- Often used for "real version": semantic versioning i.e. `mylib.so.1.2.4` (e.g. MongoDB - OGRE3D, but there, the "real name"=soname is also the soname)
- Have `mylib.so.1` be a symlink to the highest "real version"
- Have the library `mylib.so` be a symlink to `mylib.so.1`
- Avoid symbol versioning - too complicated

## Symbol visibility

- don't rely on "static" keyword
- Use `-fvisibility=hidden` or `-fvisibility=default` exclusively (when library is small, the latter is ok)
- Use `-fvisibility=hidden` when also compiling for Windows (similar erros on both platforms)
- Use `-fvisibility-inlines-hidden` and be sure to never do anything with and inline function pointer than to call it
- Don't use `__attribute__ (visibility=hidden)` on namespaces (gcc only). This will make porting to other compilers harder

# Best Practices on Windows

## Building

- Compile with warnings level `W2`.
- Assemble all dlls into the same path as the executable to have simpler loading.
- When dynamically loading library functions, export the functions via `extern "C"`. When loading classes, provide constructor and deletion factories to circumvent issues with `new` and `delete` overloads.

## Versioning

- Not really possible.

## Symbol visibility

- Define a macro for `__declspec ( dllexport )` and `__declspec( dllimport )` according to building or consuming headers, even if it is not really relevant very often.
