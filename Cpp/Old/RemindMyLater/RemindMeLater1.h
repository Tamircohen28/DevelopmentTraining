#pragma once

namespace RML1
{
	/*
	funtions add new reminder to calander
	*/
	void add_reminder(char **&calander, size_t &index);

	/*
	funtions deletes reminder from calander
	*/
	void del_reminder(char **&calander, size_t &index);

	void print_calander(char **const calander);

	/**
	 * RML1 main function
	 * function to manage reminders list as cycle buffer
	 * @param reminder_buf must have allocated memory on heap
	 */
	void calander(char **&reminder_buf);

	enum OptionsEnum
	{
		E_DEL = 0,
		E_ADD = 1,
		E_PRINT_MEETINGS = 2,
		E_EMPTY = 3,
	};

	const int ENUM_ARR[] = {E_DEL, E_ADD, E_PRINT_MEETINGS};
}