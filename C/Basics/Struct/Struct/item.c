#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct item
{
	char *itemName;
	size_t quantity;
	float price;
	float amount;
};

void read_item(struct item *sitem_ptr) {
	printf("Insert item name (String):\n");
	scanf("%s", sitem_ptr->itemName);

	printf("Insert item price (float):\n");
	scanf("%f", &(sitem_ptr->price));

	printf("Insert item quantity (size_t):\n");
	scanf("%d", &(sitem_ptr->quantity));

	// update amount
	sitem_ptr->amount = (sitem_ptr->quantity) * (sitem_ptr->price);
}


void print_item(struct item *sitem_ptr) {
	printf("\nItem %s Data:\n Price: %.2f\n Quentity: %d\n Amount: %.2f\n", sitem_ptr->itemName, sitem_ptr->price, sitem_ptr->quantity, sitem_ptr->amount);
}


int main() {
	// allocate memory
	struct item *sitem_ptr = (struct item *)malloc(sizeof(struct item));
	sitem_ptr->itemName = (char *)malloc(30 * sizeof(char));

	// if falid to allocate memory
	if (sitem_ptr->itemName == NULL) {
		exit(-1);
	}

	read_item(sitem_ptr);

	print_item(sitem_ptr);
	return 0;
}