#include <iostream>
#include <string>
#include "RemindMeLater1.h"
// #include "RemindMeLater2.h"
#define MEM_ERR "\nEnable to allocte memory!"
#define BUFFER_SIZE 3
#define NAME_SIZE 30
#define MANU "$> Enter 0 to del reminder \n$> Enter 1 to add new reminder \n$> Enter 2 to print meetings only"

// crypto higher then cyber
enum praiority
{
    E_HIGHEST = 5,
    E_CYPBER = 3,
    E_CRYPTO = 4,
    E_MEETING = 2,
    E_DEFUALT = 1
};

enum class m_types {CYBER, CRYPTO, MEETING, DEFUALT, NONE};

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

void print_reminder(reminder*& r_ptr, bool print_invited = false);

void print_calander(reminder**& calander, bool print_full = false, m_types specific_type = m_types::NONE);

void rec_invited(reminder*& p_reminder);

void rec_reminder(reminder*& p_reminder); 

void add_reminder(reminder**& calander, size_t& index);

void del_reminder(reminder**& calander, size_t& index); 

size_t find_spcae(reminder**& array);

bool is_enum(int val); 

size_t get_action(); 

void RML3_func(reminder**& reminder_buf);
