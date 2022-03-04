#pragma once
#include <iostream>

// crypto higher then cyber
enum praiority
{
    E_HIGHEST = 5,
    E_CYPBER = 3,
    E_CRYPTO = 4,
    E_MEETING = 2,
    E_DEFUALT = 1
};

enum class m_types { CYBER, CRYPTO, MEETING, DEFUALT, NONE };

// new type
struct reminder
{
    char* ptr;
    uint8_t severity;
    m_types type;
    char* invited;
    uint8_t N_invited;
    uint16_t called;
};

namespace RML3 {

    /* print reminder, can also print people invited to meetings */
    void print_reminder(reminder*& r_ptr, bool print_invited);

    /* print reminder, can also print people invited to meetings, can print specific type only */
    void print_calander(reminder**& calander, bool print_full, m_types specific_type);

    /* user IO to recive invited people to mmetings */
    void rec_invited(reminder*& p_reminder);

    /* user IO to recive reminders */
    void rec_reminder(reminder*& p_reminder);

    /* adds reminder to calander */
    void add_reminder(reminder**& calander, size_t& index);

    /* delete reminder from calander */
    void del_reminder(reminder**& calander, size_t& index);

    /* finds empty index in array */
    size_t find_spcae(reminder**& const array);

    /* if a iven value is in the enum array */
    bool is_enum(int val);

    /* checks if str start with pre */
    bool prefix_match(const char* str, const char* pre);

    /* user IO manu */
    size_t get_action();

    /* main function of RML3 */
    void RML3_func(reminder**& reminder_buf);
}