#include <iostream>
#include <string>
#include "RemindMeLater1.h"
#include "RemindMeLater2.h"
#define MEM_ERR "\nEnable to allocte memory!"
#define BUFFER_SIZE 3

enum praiority
{
    E_HIGHEST = 5,
    E_CYPBER = 4,
    E_CRYPTO = 3,
    E_MEETING = 2,
    E_DEFUALT = 1
};

void RML2::print_reminder(reminder* r_ptr) {

    if (r_ptr != nullptr) {

        std::cout << "<Sevr>: " << (int)r_ptr->severity << std::endl;

        if (r_ptr->ptr != nullptr) {
            std::cout << "<Data>: " << r_ptr->ptr << std::endl;
        }
        else
        {
            std::cout << "<Data>: " << "NULL" << std::endl;
        }
    }
    else {
        std::cout << "<Sevr>: " << "NULL" << std::endl;
        std::cout << "<Data>: " << "NULL" << std::endl;
    }
}

void RML2::print_calander(reminder**& calander) {
    std::cout << "----------- Calander ------------" << std::endl;
    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        std::cout << "\nPrint Reminer [" << i << "]:" << std::endl;
        print_reminder(calander[i]);
    }
    std::cout << "---------------------------------\n" << std::endl;
}

bool RML2::prefix_match(const char* str, const char* pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

void RML2::rec_reminder(reminder*& p_reminder) {
    size_t length = 0;
    std::cout << "\nEnter reminder length:" << std::endl;
    std::cin >> length;

    
    reminder* p_reminder_temp = (reminder*)calloc(1, sizeof(reminder));
    if (!p_reminder_temp) {
        std::cout << __LINE__ << MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    // reminder length + '\0'
    char* data_temp = (char*)calloc(length + 1, sizeof(char));
    if (!data_temp) {
        std::cout << __LINE__ << MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "\nEnter reminder:" << std::endl;
    // discards the input buffer 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(data_temp, length);

    // insert severity
    if (prefix_match(data_temp, "Cyber")) {
        p_reminder_temp->severity = E_CYPBER;
    }
    else if (prefix_match(data_temp, "Crypto"))
    {
        p_reminder_temp->severity = E_CRYPTO;
    }
    else if (prefix_match(data_temp, "Meetings"))
    {
        p_reminder_temp->severity = (uint8_t)E_MEETING;
    }
    else {
        p_reminder_temp->severity = (uint8_t)E_DEFUALT;
    }

    // move new pointer to refrence pointer
    p_reminder_temp->ptr = data_temp;
    free(p_reminder);
    p_reminder = p_reminder_temp;
    data_temp = nullptr;
    p_reminder_temp = nullptr;
}

void RML2::add_reminder(reminder**& calander, size_t& index) {
    // recive new reminder
    reminder* p_reminder = nullptr;
    rec_reminder(p_reminder);

    // free reminder im overriting
    if (calander[index] != nullptr) {
        free(calander[index]);
    }
    calander[index] = p_reminder;
    p_reminder = nullptr;

    index = (index + 1) % BUFFER_SIZE;
}

void RML2::del_reminder(reminder**& calander, size_t& index) {
    size_t lowest_severity = praiority::E_HIGHEST;
    size_t del_index = (index + BUFFER_SIZE - 1) % BUFFER_SIZE;

    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        // case of nullptr
        if (!calander[i]) {
            continue;
        }

        if (calander[i]->severity < lowest_severity) {
            lowest_severity = calander[i]->severity;
            del_index = i;
        }
    }

    // check if i can delete
    if (calander[del_index] != nullptr) {
        // delete last reminder
        free(calander[del_index]);
        calander[del_index] = nullptr;
        index = del_index;
        std::cout << "\n&> delete at index [" << del_index << "] was succsesful!\n" << std::endl;
    }
    else
    {
        std::cout << "\n[ERR]: can't delete, Calander is empty!\n" << std::endl;
    };
}

size_t RML2::find_spcae(reminder**& const array) {
    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (array[i] == nullptr) {
            return i;
        }
    }
    return 0;
}

void RML2::RML2_func(reminder**& reminder_buf) {
    size_t index = 0;
    size_t option = RML1::OptionsEnum::E_EMPTY;

    while (true)
    {
        print_calander(reminder_buf);

        option = RML1::OptionsEnum::E_EMPTY;
        while (option != RML1::OptionsEnum::E_ADD && option != RML1::OptionsEnum::E_DEL)
        {
            std::cout << "$> Enter 0 to delete reminder or 1 to add a new one:" << std::endl;
            std::cin >> option;
            if (option != RML1::OptionsEnum::E_ADD && option != RML1::OptionsEnum::E_DEL) {
                std::cout << "$> Input not valid try again!\n" << std::endl;
            }
        }
        index = find_spcae(reminder_buf);
        
        switch (option)
        {
        case RML1::OptionsEnum::E_ADD: {
            add_reminder(reminder_buf, index);
            break;
        }
        case RML1::OptionsEnum::E_DEL: {
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

//void main() {
//    reminder** calander = (reminder**)calloc(BUFFER_SIZE, sizeof(reminder*));
//    RML2::RML2_func(calander);
//}