#include "GroceryItem.h"

// Constructor sets the name and starting quantity
GroceryItem::GroceryItem(string itemName, int itemQuantity) 
{
	name = itemName;
	quantity = itemQuantity;

}

// Return the grocery item's name
string GroceryItem::getName() 
{
	return name;

}

//Return the grocery item's quantity
int GroceryItem::getQuantity() 
{
	return quantity;

}

// Increase the quantity when another item is found
void GroceryItem::addItem() 
{
	quantity++;

}
