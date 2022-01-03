
#include <stdio.h>
#include <stdbool.h>

struct employee {
	char name[20];
	int hireDate;
	float salary;
};

void printEmployee(struct employee const *e1) {
	printf("Employee:\n Name: %s\n Hire Date: %d\n Salary: %.2f\n", e1->name, e1->hireDate, e1->salary);
}

int main2() {
	struct employee e1 = {"Tamir Cohen", 1000, 125.25};
	printEmployee(&e1);
	return 0;
}