# Libraries and Symbol visibility

## Example 1: Symbol visibility in a shared library

Compile:

`cl /EHsc /LD visible_library.cpp /link /out:visible_library.dll`

Link:

`cl /EHsc linking_a_shared_library.cpp /I ..\ /link ..\library_visibility\visible_library.lib`

Now we get errors, because not all symbols were exported:

- First error reads: `error LNK2019: Reference to undefined external symbol ""unsigned __int64 __cdecl my_lib_visibility::factorial(unsigned __int64)" (?factorial@my_lib_visibility@@YA_K_K@Z)" in function "main"`
- Exporting is exactly, what the `__declspec( dllexport )` does. See for instance `dumpbin /EXPORTS visible_library.dll`, we find:
- We only see:

1    0 00001000 ?computeNchooseK@my_lib_visibility@@YA_K_K0@Z
2    1 0000F2B0 ?static_variable@my_lib_visibility@@3_KB

- Second error reads: `error LNK2019: Reference to undefined external symbol ""unsigned __int64 const my_lib_visibility::static_variable" (?static_variable@my_lib_visibility@@3_KB)" in function "main"`
- But the symbol is present, isn't it? Well, we have to import it.
- In `visible_library.hpp` change `__declspec( dllexport )` to `__declspec( dllimport )` (don't recompile!)

Now everything works. In general:

- If you only refer to functions, no need to `dllimport` (but performance gain), 
- when referring to data (or functions with definition in the header!), need to use `dllimport`.

Therefore, use preprocessor macros to switch everywhere.

## Example 2: Link static into dynamic library

TODO

## Example 3: Symbol visibility and classes

Compile:

`cl /EHsc /LD shape.cpp /link /out:shape_library.dll`

Have a look at the exported symbols (to demangle, use dependency walker):

shape_lib::Shape::Shape(class shape_lib::Shape const &)
shape_lib::Shape::Shape(unsigned int)
shape_lib::Shape::~Shape(void)
class shape_lib::Shape & shape_lib::Shape::operator=(class shape_lib::Shape const &)
const shape_lib::Shape::`vftable'
void shape_lib::Shape::draw(void)

We have additional functions:
- generated copy constructor
- generated assignment operator
- vftable (vtable)

Those are absent when exporting the functions only:

Link:

`cl /EHsc using_shape.cpp /I ..\ /link ..\shared_class\shape.lib`

Note: We can change the implementation of the function draw. As long as we don't change the ABI, we can change everything, as the library is only loaded at startup time.

## Example 4: Problems with the std library

Compile:

`cl /EHsc /LD shape_with_ptr.cpp /link /out:shape_library.dll`

We get the warning 

`class "std::shared_ptr<shape_lib::CornerNumber>" requires a dll-interface to be used by clients of class "shape_lib::Shape"`

even if `CornerNumber` itself is dll-exported. 

- This is related to the problem shown in Example 5 and the fact that no member of the STL is `__declspec ( dllexport )`. 
- In this case, nothing can happen if no function is inline and the member cannot be accessed
- In general, porting standard library (especiall STL objects) across dll borders is not a good idea for real libraries
- see (<https://stackoverflow.com/questions/22797418/how-do-i-safely-pass-objects-especially-stl-objects-to-and-from-a-dll>)

## Example 5: Exposing function symbols instead of classes

More information on <https://msdn.microsoft.com/library/esew7y1w.aspx>

If we export the whole class, we get a warning (on level W2 at least):

`class "shape_lib::CornerNumber" requires a dll-interface to be used by clients of class "shape_lib::Shape"`

However, when exporting only functions, we get:

`cl /EHsc /LD /W2 shape.cpp corner_number.cpp /link /out:shape_library.dll`

Link:

`cl /EHsc /W2 using_square.cpp square.cpp /I ..\ /link ..\shared_class\shape.lib`

and inheritance works fine.

Note: If we inline the function `draw` with access to `CornerNumber`, we have to use `__declspec( dllimport )` (see also first example). If this is done, everything still works.