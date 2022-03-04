// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
constexpr int OPCODE_OFFSET = 5;
constexpr int OPCODE_SIZE = 2;

// mpping value to opcode
enum OPCODE_DICT {
    E_ADD_USER = 0x01,
    E_ADD_ACK = 0x02,
    E_DEL_USER = 0x03,
    E_DEL_ACK = 0x04
};

// mapping opcode to function
enum OPCODE_FUNC_DICT {
    E_FUNC_ADD_USER = 0,
    E_FUNC_ADD_ACK = 1,
    E_FUNC_DEL_USER = 2,
    E_FUNC_DEL_ACK = 3
};

void add_user_func() {
    std::cout << "add_user_func" << std::endl;
}

void add_ack_func() {
    std::cout << "add_ack_func" << std::endl;
}

void del_user_func() {
    std::cout << "del_user_func" << std::endl;
}

void del_ack_func() {
    std::cout << "del_ack_func" << std::endl;
}

// array of message functions
constexpr void (*msg_functions[])() = { add_user_func, add_ack_func, del_user_func, del_ack_func };

// function to build opcode bytes into opcode value
int build_value(const void* const ptr, size_t length, int base = 10) {
    int result = 0;

    for (size_t i = 0; i < length; i++)
    {
        result += (int)*((uint8_t*)ptr + i) * pow(base, i);
    }

    return result;
}


void msg_switch(const void* const msg_ptr, size_t msg_len) {
    // cast opcode from message
    int opcode_val = build_value(((uint8_t*)msg_ptr + OPCODE_OFFSET), OPCODE_SIZE);

    std::cout << "Opcode is: " << opcode_val << std::endl;

    switch (opcode_val) {
    case OPCODE_DICT::E_ADD_USER:
        msg_functions[OPCODE_FUNC_DICT::E_FUNC_ADD_USER]();
        break;

    case OPCODE_DICT::E_ADD_ACK:
        msg_functions[OPCODE_FUNC_DICT::E_FUNC_ADD_ACK]();
        break;

    case OPCODE_DICT::E_DEL_USER:
        msg_functions[OPCODE_FUNC_DICT::E_FUNC_DEL_USER]();
        break;

    case OPCODE_DICT::E_DEL_ACK:
        msg_functions[OPCODE_FUNC_DICT::E_FUNC_DEL_ACK]();
        break;

    default:
        std::cout << "[ERR]: not valid opcode: " << opcode_val << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{
    uint8_t temp[] = {0, 0, 0, 0, 0, 2, 0, 2 , 1, 5};
    msg_switch(&temp, 10);
}

