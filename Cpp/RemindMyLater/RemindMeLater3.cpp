#include <iostream>
#include <string>
#include "RemindMeLater1.h"
#include "RemindMeLater3.h"
#define MEM_ERR "\nEnable to allocte memory!"
#define BUFFER_SIZE 3
#define NAME_SIZE 30
#define MANU "$> Enter 0 to del reminder \n$> Enter 1 to add new reminder \n$> Enter 2 to print meetings only"

void RML3::print_reminder(reminder*& r_ptr, bool print_invited = false) {

    if (r_ptr != nullptr) {
        std::cout << "<Urgent>: " << (int)r_ptr->called << std::endl;
        std::cout << "<Sevr>: " << (int)r_ptr->severity << std::endl;

        if (r_ptr->ptr != nullptr) {
            std::cout << "<Data>: " << r_ptr->ptr << std::endl;
        }
        else
        {
            std::cout << "<Data>: " << "NULL" << std::endl;
        }

        if (print_invited) {
            if (r_ptr->invited != nullptr) {
                std::cout << "<Num Invited>: " << (int)r_ptr->N_invited << std::endl;
                std::cout << "<Invited>: " << r_ptr->invited << std::endl;
            }
            else
            {
                std::cout << "<Num Invited>: " << "NULL" << std::endl;
                std::cout << "<Invited>: " << "NULL" << std::endl;
            }
        }
        r_ptr->called += 1;
    }
    else {
        std::cout << "<Sevr>: " << "NULL" << std::endl;
        std::cout << "<Data>: " << "NULL" << std::endl;
    }
}

void RML3::print_calander(reminder**& calander, bool print_full = false, m_types specific_type = m_types::NONE) {
    std::cout << "----------- Calander ------------" << std::endl;
    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (specific_type != m_types::NONE) {
            if (calander[i] != nullptr) {

                // check for specific type
                if (calander[i]->type == specific_type) {
                    std::cout << "\nPrint Reminer [" << i << "]:" << std::endl;
                    print_reminder(calander[i], print_full);
                }
                else {
                    continue;
                }
            }
        }
        else {
            std::cout << "\nPrint Reminer [" << i << "]:" << std::endl;
            print_reminder(calander[i], print_full);
        }

    }
    std::cout << "---------------------------------\n" << std::endl;
}


void RML3::rec_invited(reminder*& p_reminder) {
    size_t num_invited = 0;
    std::cout << "\nEnter Number Invited:" << std::endl;
    std::cin >> num_invited;

    // reminder length + '\0'
    char* invited_temp = (char*)calloc(num_invited, NAME_SIZE);
    if (!invited_temp) {
        std::cout << __LINE__ << MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "\nEnter Invited Names:" << std::endl;

    // discards the input buffer 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(invited_temp, (uint64_t)num_invited * (uint64_t)NAME_SIZE);
    
    free(p_reminder->invited);
    p_reminder->invited = invited_temp;
    p_reminder->N_invited = (uint8_t)num_invited;
    invited_temp = nullptr;
}

void RML3::rec_reminder(reminder*& p_reminder) {
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
        p_reminder_temp->type = m_types::CYBER;
    }
    else if (prefix_match(data_temp, "Crypto"))
    {
        p_reminder_temp->severity = E_CRYPTO;
        p_reminder_temp->type = m_types::CRYPTO;
    }
    else if (prefix_match(data_temp, "Meetings"))
    {
        p_reminder_temp->severity = (uint8_t)E_MEETING;
        p_reminder_temp->type = m_types::MEETING;
        rec_invited(p_reminder_temp);
    }
    else {
        p_reminder_temp->severity = (uint8_t)E_DEFUALT;
        p_reminder_temp->type = m_types::DEFUALT;
    }

    // move new pointer to refrence pointer
    p_reminder_temp->ptr = data_temp;
    free(p_reminder);
    p_reminder = p_reminder_temp;
    data_temp = nullptr;
    p_reminder_temp = nullptr;
}

void RML3::add_reminder(reminder**& calander, size_t& index) {
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

void RML3::del_reminder(reminder**& calander, size_t& index) {
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

size_t RML3::find_spcae(reminder**& const array) {
    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (array[i] == nullptr) {
            return i;
        }
    }
    return 0;
}

bool RML3::prefix_match(const char* str, const char* pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}


bool RML3::is_enum(int val) {
    for (int i = 0; i < (sizeof(RML1::ENUM_ARR) / sizeof(*RML1::ENUM_ARR)); i++)
    {
        if (RML1::ENUM_ARR[i] == val) { 
            return true; 
        }
    }
    return false;
}

size_t RML3::get_action() {
    size_t option = RML1::OptionsEnum::E_EMPTY;
    option = RML1::OptionsEnum::E_EMPTY;

    while (!is_enum(option))
    {
        std::cout << MANU << std::endl;
        std::cin >> option;
        if (!is_enum(option)) {
            std::cout << "$> Input not valid try again!\n" << std::endl;
        }
    }

    return option;
}


void RML3::RML3_func(reminder**& reminder_buf) {
    size_t index = 0;
    size_t option = RML1::OptionsEnum::E_EMPTY;

    while (true)
    {
        print_calander(reminder_buf);
        option = get_action();
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
        case RML1::OptionsEnum::E_PRINT_MEETINGS: {
            print_calander(reminder_buf, true, m_types::MEETING);
            break;
        }
        default: {
            std::cout << "\n[ERR]: Invalid option!\n" << std::endl;
            break;
        }
        }
    }
}

int main() {
    reminder** calander = (reminder**)calloc(BUFFER_SIZE, sizeof(reminder*));
    RML3::RML3_func(calander);
    return 0;
}