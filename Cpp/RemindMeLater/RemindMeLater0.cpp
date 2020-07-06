#include <iostream>
#include <string>
#include "RemindMeLater0.h"
#define MEM_ERR "\nEnable to allocte memory!"

/*
Remind Me later level 0
*/

void RML0::print_reminder(const char* const p_reminder) {

    if (p_reminder != nullptr) {
        std::cout << "~~ Reminder:\n" << p_reminder << std::endl;
    }
    else {
        std::cout << "~~ Reminder:\n" << "NULL" << std::endl;
    }
}


void RML0::rec_reminder(char*& p_reminder) {

    size_t length = 0;
    std::cout << "\nEnter reminder length:" << std::endl;
    std::cin >> length;

    // reminder length + '\0'
    char* temp = (char*)calloc(length + 1, sizeof(char));

    if (!temp) {
        std::cout << __LINE__ << MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "\nEnter reminder:" << std::endl;
    // discards the input buffer 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(temp, length);

    free(p_reminder);
    p_reminder = temp;
    temp = nullptr;
}


void RML0::reminder_in() {

    char* p_reminder = NULL;
    while (true)
    {
        print_reminder(p_reminder);
        rec_reminder(p_reminder);
    }
}