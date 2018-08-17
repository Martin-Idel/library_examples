#include <windows.h> 

#include <iostream>
#include <cstdint>

#include "first_library/first_library.hpp"

int main()
{
	LPCSTR library_name = TEXT("first_dynamic_library.dll");
	HMODULE my_lib_handle = LoadLibrary(library_name);

	if(my_lib_handle==NULL) {
		std::cout << "Library could not be opened" << std::endl;
        return 0;
	}

    uint64_t (*addingTwoNumbers)(uint64_t, uint64_t) = reinterpret_cast<uint64_t (*)(uint64_t, uint64_t)>(
		GetProcAddress(my_lib_handle, "addingTwoNumbers"));

	if(addingTwoNumbers==NULL) {
		std::cout << "Function could not be loaded" << std::endl;
        FreeLibrary(my_lib_handle);
        return 0;
	}

    std::cout << (*addingTwoNumbers)(10, 20) << std::endl;

    FreeLibrary(my_lib_handle);
	return 0;
}