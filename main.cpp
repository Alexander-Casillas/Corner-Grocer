#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "GroceryItem.h"
#include <limits>

using namespace std;

// Reads the inventory file and counts grocery purchases
// @returns a map containing grocery items and their quantities
map<string, GroceryItem*> readInventory() 
{
	map<string, GroceryItem*> items;
	ifstream inputFile("inventory.txt");
	string name;

	// Check that the inventory file is open
	if (!inputFile.is_open()) 
	{
		cout << "Error: Could not open inventory.txt" << endl;
		return items;

	}

	// Read each grocery item from the file
	while (inputFile >> name) 
	{
		// Check whether the item already exists
		if (items.count(name) > 0) 
		{
			items.at(name)->addItem();

		}

		else 
		{
			//Create a new grocery item with a quantity of 1
			GroceryItem* newItem = new GroceryItem(name, 1);
			items.emplace(name, newItem);

		}
	}

	inputFile.close();
	return items;
}

// Creates a backup file containing grocery item frequencies
// @param items - Map containing grocery items and their quantities
void createBackup(map<string, GroceryItem*>& items) 
{

	// Open the backup file for writing
	ofstream outputFile("frequency.dat");

	if (!outputFile.is_open()) 
	{
		cout << "Error: could not create frequency.dat" << endl;

		return;

	}

	//Write each grocery item and the quantity
	for (map<string, GroceryItem*>::iterator it = items.begin();
		it != items.end(); ++it) 
	{
		outputFile << it->second->getName()
			<< " "
			<< it->second->getQuantity()
			<< endl;

	}

	outputFile.close();

}

// Runs the corner grocer menu and processes user selections
// @returns 0 when the program exits normally
int main() 
{
	cout << "Corner Grocer Program" << endl;

	// Read the grocery inventory
	map<string, GroceryItem*> items = readInventory();

	// Automatically create a backup file
	createBackup(items);

	// Release the memory used by grocery items
	for (map<string, GroceryItem*>::iterator it = items.begin();
		it != items.end(); ++it)
	{
		delete it->second;
	}

	const int SEARCH_OPTION = 1;
	const int FREQUENCY_OPTION = 2;
	const int HISTOGRAM_OPTION = 3;
	const int EXIT_OPTION = 4;
	int choice = 0;

	// Continue to display the menu until user chooses to exit
	while (choice != EXIT_OPTION) 
	{
		cout << "\nCorner Grocer Menu" << endl;
		cout << "1. Search for an item" << endl;
		cout << "2. Display all item frequencies" << endl;
		cout << "3. Display frequency histogram" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice from 1 to 4: ";
		cin >> choice;

		//Check if the user entered a number
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input. Please enter a number from 1 to 4." << endl;
			continue;

		}

		switch (choice) 
		{
		case SEARCH_OPTION: 
		{

			// Reload the inventory to get current data
			map<string, GroceryItem*> currentItems = readInventory();

			string itemName;
			cout << "Enter the grocery item to search for: ";
			cin >> itemName;

			// Check if the item exists in the inventory
			if (currentItems.count(itemName) > 0) 
			{
				cout << itemName
					<< " "
					<< currentItems.at(itemName)->getQuantity()
					<< endl;

			}

			else 
			{
				cout << "Item not found." << endl;

			}

			// Release memory used by the current inventory
			for (map<string, GroceryItem*>::iterator it = currentItems.begin();
				it != currentItems.end(); ++it)
			{
				delete it->second;

			}

			break;
		}

		case FREQUENCY_OPTION: 
		{

			// Reload the inventory to get current data
			map<string, GroceryItem*> currentItems = readInventory();

			cout << "\nGrocery Item Frequencies" << endl;

			// Display each item and its quantity
			for (map<string, GroceryItem*>::iterator it = currentItems.begin();
				it != currentItems.end(); ++it)
			{
				cout << it->second->getName() << " "
					<< it->second->getQuantity() << endl;

			}

			// Release memory used by the current inventory
			for (map<string, GroceryItem*>::iterator it = currentItems.begin();
				it != currentItems.end(); ++it)
			{
				delete it->second;

			}

			break;
		}

		case HISTOGRAM_OPTION: 
		{

			// Reload the inventory to get current data
			map<string, GroceryItem*> currentItems = readInventory();

			cout << "\nGrocery Item Histogram" << endl;

			// Display each item with asterisks to match its quantity
			for (map<string, GroceryItem*>::iterator it = currentItems.begin();
				it != currentItems.end(); ++it)
			{
				cout << it->second->getName() << " ";

				for (int i = 0; i < it->second->getQuantity(); ++i) 
				{
					cout << "*";

				}

				cout << endl;

			}

			// Release memory used by the current inventory
			for (map<string, GroceryItem*>::iterator it = currentItems.begin();
				it != currentItems.end(); ++it)
			{
				delete it->second;

			}

			break;
		}

		case EXIT_OPTION:
			cout << "Thank you for using Corner Grocer" << endl;
			break;

		default:
			cout << "Invalid selection. Please select options 1 through 4" << endl;
		}
	}

	return 0;
}