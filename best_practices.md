# Best Practices

## Building

- Use the rpath of a `.so` instead of relying on the `LD_LIBRARY_PATH`.
- Always build with `-fPIC` option (don't use `-fpic` and don't omit), as shared libraries need it.

## Versioning

### SONAME versioning

- Coarse grained. If library changes fast, this is probably not very good
- Increase SONAME version when ABI changes, i.e. `mylib.so.1`
- Format or "real name" is not fixed. In glibc it is "current, revision, age", where "age" reflects backwards compatibility.
- Often used for "real version": semantic versioning i.e. `mylib.so.1.2.4` (e.g. MongoDB - OGRE3D, but there, the "real name"=soname is also the soname)
- Have `mylib.so.1` be a symlink to the highest "real version"
- Have the library `mylib.so` be a symlink to `mylib.so.1`.

### Symbol versioning

- Better than SONAME as not so coarse grained
- Way more complicated, avoid...

## Symbol visibility

- don't rely on "static" keyword
- Use `-fvisibility=hidden` or `-fvisibility=default` exclusively (when library is small, the latter is ok)
- Use `-fvisibility=hidden` when also compiling for Windows (similar erros on both platforms)