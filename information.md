# Additional information

## General

<https://lwn.net/Articles/276782/>

## ELF

<http://tldp.org/HOWTO/Program-Library-HOWTO/shared_libraries.html>
<http://anadoxin.org/blog/control-over-symbol-exports-in-gcc.html>
<https://gcc.gnu.org/wiki/Visibility>
<https://www.ibm.com/developerworks/aix/library/au-aix-symbol-visibility/index.html>
<https://www.mpcdf.mpg.de/services/computing/software/libraries/static-and-dynamic-linking-on-linux-systems>
<https://www.ibm.com/developerworks/aix/library/au-aix-symbol-visibility-part2/index.html>
<https://www.tldp.org/HOWTO/html_single/C++-dlopen/>
<https://jvns.ca/blog/2014/09/06/how-to-read-an-executable/>
<https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/>
<https://eli.thegreenplace.net/2011/11/03/position-independent-code-pic-in-shared-libraries/>
<https://www.symantec.com/connect/articles/dynamic-linking-linux-and-windows-part-one>

## PE

<https://adrianhenke.wordpress.com/2008/12/05/create-lib-file-from-dll/>
<https://www.symantec.com/connect/articles/dynamic-linking-linux-and-windows-part-two>

## Environment Variables

LD_DEBUG

- `export LD_DEBUG=files` (outputs file processing)
- `export LD_DEBUG=bindings` (outputs information about symbol bindings)
- `export LD_DEBUG=libs` (outputs library search paths)
- `export LD_DEBUG=versions` (outputs dependency versions)
- `export LD_DEBUG=help` (outputs options when trying to run program)
- `export LD_DEBUG=statistics` (outputs symbol statistics)

## Programs

- `objdump`, `readelf` or `nm` to get information about binaries on linux, `dumpbin` on Windows
- `ldd` see dependencies
- `lddtree` see complete tree of dependencies (similar to `dependencywalker` on Windows)
- `patchelf` can patch linker information, e.g. sonames (don't do it)