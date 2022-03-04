#pragma once
#include <iostream>


struct reminder
{
    char* ptr;
    uint8_t severity;
};

namespace RML2 {
    /* prints reminder (severity and data) */
    void print_reminder(reminder* r_ptr);

    /* prints calander */
    void print_calander(reminder**& calander);

    /* checks if str starts with pre */
    bool prefix_match(const char* str, const char* pre);

    /* recieves reminder from user */
    void rec_reminder(reminder*& p_reminder);

    /* add reminder to the calander */
    void add_reminder(reminder**& calander, size_t& index);

    /* delete reminder from the calander */
    void del_reminder(reminder**& calander, size_t& index);

    /* recives the calander and returns the first emprt spot in the array */
    size_t find_spcae(reminder**& const array);

    /**
     * RML2 main function
     * function to manage calander by severty of reminders
     * @param reminder_buf must have allocated memory on heap
     */
    void RML2_func(reminder**& reminder_buf);
}