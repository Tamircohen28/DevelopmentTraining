#pragma once
#include <iostream>
#define DEBUG true
#define ERR_MSG "[ERR]: Falied to allocate memory"
#define FREE_MSG "[INFO]: Needed to free pointer"

namespace templates {
    // Array struct
    template<typename T>
    struct s_arr
    {
        T* ptr;
        size_t size;
    };

    // Print given pointer in a given casting
    template<typename T, typename cast>
    void print_add(const T* const ptr) {
        std::cout << "Current add: " << cast(ptr) << std::endl;
    }

    /**
     * Allocates new memory in the heap
     * @param ptr must be null or heap pointer
     * @return pointr to new memory located
     */
    template<typename T>
    T* talloc(T* ptr, size_t current_size, size_t add_size)
    {
        std::cout << "TALLOC " << current_size << " " << add_size << std::endl;
        T* temp = nullptr;

        // allocating new mem
        if (current_size == 0) {
            temp = (T*)calloc(1, add_size);
        }
        else
        {
            // realloc frees ptr 
            temp = (T*)realloc(ptr, current_size + add_size);
        }

        // fail to allocate
        if (!temp) {
            std::cout << ERR_MSG << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "END TALLOC" << std::endl;
        return temp;
    }


    /**
     * Updates the size of pointer and addes the var, use only for non-array types
     * @param ptr must be null or heap pointer
     * @return size of given variable, updates original pointer
     */
    template <typename T>
    size_t size(uint8_t*& ptr, size_t& current_size, T var)
    {
#if DEBUG
        std::cout << "S1:" << std::endl;
        std::cout << (int)current_size << std::endl;
        print_add<uint8_t, int>(ptr);
#endif // DEBUG

        // allocating new mwm
        ptr = talloc(ptr, current_size, sizeof(var));

        // copy new data to pointer
        memcpy((ptr + current_size), &var, sizeof(var));
        current_size += sizeof(var);

#if DEBUG
        print_add<uint8_t, int>(ptr);
        std::cout << std::endl;
#endif // DEBUG

        return sizeof(var);
    }

    /**
     * Updates the size of pointer and addes the var, use only for array types
     * @param ptr must be null or heap pointer
     * @return size of given variable, updates original pointer
     */
    template<typename T>
    size_t size(uint8_t*& ptr, size_t& current_size, s_arr<T> Arr) {
#if DEBUG
        std::cout << "S2:" << std::endl;
        std::cout << (int)current_size << std::endl;
        print_add<uint8_t, int>(ptr);
#endif // DEBUG

        // allocating new memory
        ptr = talloc(ptr, current_size, Arr.size);

        // copy new data to pointer
        memcpy((ptr + current_size), Arr.ptr, Arr.size);
        current_size += Arr.size;

#if DEBUG
        print_add<uint8_t, int>(ptr);
        std::cout << std::endl;
#endif // DEBUG

        return (Arr.size);
    }

    /**
     * Generic funtion to nuild a message of unknown number of variables
     * of unkwnown types
     * @param uint8_t* ptr -> pointer to heap or nullptr
     * @param size_t current_size -> number of bytes pointed to by ptr
     * @param first & args are unknown variables
     * @return size of message, updates original pointer to point to message
     */
    template<typename T, typename... Args>
    size_t size(uint8_t*& ptr, size_t current_size, T first, Args... args) {
        return size(ptr, current_size, first) + size(ptr, current_size, args...);
    }

    // prints the value of an address in memory
    void print_cell(int address);
}
