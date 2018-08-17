#include <dlfcn.h>

#include <iostream>
#include <cstdint>

#include "first_library/first_library.hpp"

int main()
{
	void * my_lib_handle = dlopen("libfirst_shared.so",RTLD_NOW);

	if(my_lib_handle==NULL) {
		std::cout << "Library could not be opened" << std::endl;
        return 0;
	}
    uint64_t (*addingTwoNumbers)(uint64_t, uint64_t) = reinterpret_cast<uint64_t (*)(uint64_t, uint64_t)>(dlsym(my_lib_handle,"_ZN6my_lib16addingTwoNumbersEmm"));
    // uint64_t (*addingTwoNumbers)(uint64_t, uint64_t) = reinterpret_cast<uint64_t (*)(uint64_t, uint64_t)>(dlsym(my_lib_handle,"addingTwoNumbers"));

	if(addingTwoNumbers==NULL) {
		std::cout << "Function could not be loaded" << std::endl;
        dlclose(my_lib_handle);
        return 0;
	}

    std::cout << (*addingTwoNumbers)(10, 20) << std::endl;

    dlclose(my_lib_handle);
	return 0;
}