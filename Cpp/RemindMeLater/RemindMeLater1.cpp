#include <iostream>
#include <string>
#include "RemindMeLater0.h"
#include "RemindMeLater1.h"

/*
Remind Me later level 1
*/

#define BUFFER_SIZE 5


void RML1::add_reminder(char**& calander, size_t& index) {
    // recive new reminder
    char* p_reminder = nullptr;
    RML0::rec_reminder(p_reminder);

    // free reminder im overriting
    if (calander[index] != nullptr) {
        free(calander[index]);
    }
    calander[index] = p_reminder;
    p_reminder = nullptr;

    index = (index + 1) % BUFFER_SIZE;
}


void RML1::del_reminder(char**& calander, size_t& index) {
    // move index back
    size_t temp_index = (index + BUFFER_SIZE - 1) % BUFFER_SIZE;

    // check if i can delete
    if (calander[temp_index] != nullptr) {
        // delete last reminder
        free(calander[temp_index]);
        calander[temp_index] = nullptr;
        index = temp_index;
        std::cout << "\n&> delete at index [" << index << "] was succsesful!\n" << std::endl;
    }
    else
    {
        std::cout << "\n[ERR]: can't delete at index [" << temp_index << "], it has to have data in order to be deleted!\n" << std::endl;
    };
}


void RML1::print_calander(char** const calander) {

    std::cout << "----------- Calander ------------" << std::endl;
    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        std::cout << "\nPrint Reminer [" << i << "]:" << std::endl;
        RML0::print_reminder(calander[i]);
    }
    std::cout << "---------------------------------\n" << std::endl;
}


void RML1::calander(char**& reminder_buf) {
    size_t index = 0;
    size_t option = OptionsEnum::E_EMPTY;

    while (true)
    {
        print_calander(reminder_buf);

        option = OptionsEnum::E_EMPTY;
        while (option != OptionsEnum::E_ADD && option != OptionsEnum::E_DEL)
        {
            std::cout << "$> Enter 0 to delete last reminder or 1 to add a new one:" << std::endl;
            std::cin >> option;
            if (option != OptionsEnum::E_ADD && option != OptionsEnum::E_DEL) {
                std::cout << "$> Input not valid try again!\n" << std::endl;
            }
        }

        switch (option)
        {
        case OptionsEnum::E_ADD: {
            add_reminder(reminder_buf, index);
            break;
        }
        case OptionsEnum::E_DEL: {
            del_reminder(reminder_buf, index);
            break;
        }
        default: {
            std::cout << "\n[ERR]: Invalid option!\n" << std::endl;
            break;
        }
        }
    }
}