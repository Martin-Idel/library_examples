# Useful Knowledge

## Links

<http://tldp.org/HOWTO/Program-Library-HOWTO/shared_libraries.html>
<http://anadoxin.org/blog/control-over-symbol-exports-in-gcc.html>
<https://www.ibm.com/developerworks/aix/library/au-aix-symbol-visibility/index.html>
<https://www.mpcdf.mpg.de/services/computing/software/libraries/static-and-dynamic-linking-on-linux-systems>
<https://gcc.gnu.org/wiki/Visibility>
<https://www.ibm.com/developerworks/aix/library/au-aix-symbol-visibility-part2/index.html>
<https://lwn.net/Articles/276782/>
<https://www.symantec.com/connect/articles/dynamic-linking-linux-and-windows-part-two>
<https://jvns.ca/blog/2014/09/06/how-to-read-an-executable/>
<https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/>
<https://eli.thegreenplace.net/2011/11/03/position-independent-code-pic-in-shared-libraries/>
<https://www.tldp.org/HOWTO/html_single/C++-dlopen/>

## Environment Variables

LD_DEBUG

- `export LD_DEBUG=files` (outputs file processing)
- `export LD_DEBUG=bindings` (outputs information about symbol bindings)
- `export LD_DEBUG=libs` (outputs library search paths)
- `export LD_DEBUG=versions` (outputs dependency versions)
- `export LD_DEBUG=help` (outputs options when trying to run program)

## Programs

- `objdump` to get information about binaries
- `nm` to get symbol information, i.e. `nm -CD` gives a lot of info about symbols
- `ldd` see dependencies
- `lddtree` see complete tree of dependencies (similar to `dependencywalker` on Windows)
