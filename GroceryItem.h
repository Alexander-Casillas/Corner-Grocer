#pragma once
#include <string>

using namespace std;


class GroceryItem
{
private:
	string name;
	int quantity;

public:
	// Creates a grocery item with a name and a quantity
	// @param itemName - name of the grocery item
	// @param itemQuantity - starting quantity
	GroceryItem(string itemName, int itemQuantity);

	// Return the grocery item name
	// @returns the grocery item's name
	string getName();

	// Return the quantity of the grocery item
	// @returns the current quantity
	int getQuantity();

	// Increase the grocery item's quantity by one
	void addItem();

};

