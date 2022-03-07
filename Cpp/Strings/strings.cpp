/**
    String funtions
    https://www.cplusplus.com/reference/string/string/

    @file strings.cpp
    @author Tamir Cohen
    @version 1.0 06/03/2022
*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    /* C style string (from <cstring>)*/
    char cfirst_name[7]{"Bjarne"};
    char clast_name[11]{"Stroustrup"};
    char whole_name[17];

    int first_name_length = strlen(cfirst_name); // length of string (excluding \0)
    int last_name_length = strlen(clast_name);

    strcpy(whole_name, cfirst_name); // copy string (dst, src)
    strcat(whole_name, clast_name);  // copy string (dst, src)
    int whole_name_length = strlen(whole_name);
    cout << "The length of the first name, " << cfirst_name << ", is " << first_name_length << " letters long and the length of the last name, " << clast_name << ", is " << last_name_length << " letters long. This means that the length of the whole name must be " << whole_name_length << " letters long." << endl;

    /* C++ strings (from <string>)*/
    string unformatted_full_name{"StephenHawking"};        // initial string
    string first_name{unformatted_full_name, 0, 7};        // initial string from another string, {string, start index, length}
    string last_name = unformatted_full_name.substr(7, 7); // initial using substr(start index, length)
    int pos = unformatted_full_name.find("H");             // Find position of 'H' using find()

    string formatted_full_name = first_name + last_name; // initial string, Extends the string by appending additional characters

    formatted_full_name.insert(7, " "); // insert sting at position 7
    cout << formatted_full_name << endl;

    // ------------------------------------------------

    string journal_entry_1{"Isaac Newton"};
    string journal_entry_2{"Leibniz"};

    journal_entry_1.erase(0, 6); // erase from potion 0, 6 characters

    if (journal_entry_2 < journal_entry_1)     // who is alphabetically less
        journal_entry_2.swap(journal_entry_1); // swap the data held by this strings

    cout << journal_entry_1 << "\n"
         << journal_entry_2;
}