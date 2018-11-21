#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>	
#include <cstring>
#include <iomanip>
#include <limits.h>
#include <cstdint>
#include "ArgumentManager.h"

using namespace std;




class ListOfItems {			// This class will help me to distinguish between the product name and cost from the text file.
private:
	string productName;
	double cost;

public:
	ListOfItems() {
		productName = "";
		cost = 0.0;
	}


	void setProductName(string nProductName) {
		productName = nProductName;
	}

	void setCost(double nCost) {
		cost = nCost;
	}

	string getProductName() {
		return productName;
	}

	double getCost() {
		return cost;
	}


};

struct Node {
	ListOfItems info;
	Node* link;
};

class NodeList {		// This class holds all the functions for the node
private:
	Node* first; // points to the first node
	Node* last; // points to the last node
	Node* current; // points to current node

public:

	double finalCost = 0.0; // variable to hold the total of value of all the items added up together
	int count = 0; // counter to keep count of how many items in list


	NodeList() {
		first = NULL;
		last = NULL;
	}

	void AddNode(string prodName, double nCost)			// This function creates a node
	{
		Node* newNode = new Node;

		newNode->info.setProductName(prodName);
		newNode->info.setCost(nCost);
		newNode->link = NULL;


		if (first != NULL) { // if list is already created
			current = first; // set current ptr to front of list (first)
			while (current->link != NULL) {
				current = current->link; // traverses through the linked list
			}
			current->link = newNode;
			count++;
		}
		else {	// if first == NULL make first point to the actual first node
			first = newNode;
			count++;
		}
	}

	void deleteNode(double nCost) // nCost is the maxPrice; This function deletes the node
	{
		Node* temp = first; // temp points to first
		Node* trailTemp = first; // trailTemp points to first
		Node* end = first; // end points to first
		Node* trail = 0;

		while (end->link != NULL) { // while the end of the list is not empty, traverse through the list
			trail = end; // setting trail to first
			end = end->link;
		}



		if (first == NULL)
		{
			cout << "ERROR: List is empty; nothing to delete!" << endl;
		}


		else if (end->info.getCost() == nCost) {  // if the end ptr is the equal to the item with price, then remove that item from the list
												 // and deduct that item price from the total cost of the items
			trail->link = NULL;					
			finalCost -= end->info.getCost();
			count--;
			delete end;
			return;
		}
		else if (temp->info.getCost() == nCost)
		{
				first = temp->link;
				count--;
				finalCost -= temp->info.getCost();
				delete temp;
				return;
		
		}  
		else
		{
			temp = temp->link; //start @ 2nd item in the list
			while (temp != NULL) {
				while (temp->info.getCost() == trailTemp->info.getCost())
				{
					trailTemp = temp;
					temp = temp->link;
				}
				if (temp->info.getCost() == nCost) 
				{

					while ((temp->info.getProductName() < temp->link->info.getProductName()) && (temp->info.getCost() == temp->link->info.getCost()))
					{
						trailTemp = trailTemp->link;
						temp = temp->link;
					}
					trailTemp->link = temp->link;
					count--;
					finalCost -= temp->info.getCost();
					delete temp;
					return;
				}
				trailTemp = temp;
				temp = temp->link;
			}
		}
	}


	void writeFile(ofstream& write)		// This function is to write to a new file
	{
		Node* nPtr = first;
		while (nPtr != NULL)
		{
			write << nPtr->info.getProductName() << ", " << fixed << setprecision(2) << nPtr->info.getCost() << endl;
			nPtr = nPtr->link;
		}


		write << endl << "Number of items: " << count << endl;
		write << "Cost: " << getSumCost() << endl;
	}

	void writeFile2(ofstream& write)		// This function is to write to a new file
	{
		
	}

	void writeFile3(ofstream& write)		// This function is to write to a new file
	{
		write << endl << "Number of items: 0" << endl;
		write << "Cost: 0.00";
	}

	void printList()		// This function is to print the linked list
	{
		current = first;

		while (current != NULL)
		{
			cout << current->info.getProductName() << ", ";
			cout << fixed << setprecision(2) << current->info.getCost() << endl;
			current = current->link;
		}

		cout << endl << "Number of items: " << count << endl;
		cout << "Cost: " << getSumCost() << endl;
	}


	double findMaxCost()		// This function is to find the item with the highest price
	{
		double max = 0.0; // maximum value
		current = first;

		while (current != NULL) {
			if (current->info.getCost() > max) {
				max = current->info.getCost();
			}
			current = current->link;
		}

		return max;
	}

	double findMinCost()		// This function is to find the item with the lowest price
	{
		
		current = first;
		double min = current->info.getCost(); // maximum value
		while (current != NULL) {
			if (current->info.getCost() < min) {
				min = current->info.getCost();
			}
			current = current->link;
		}
		return min;
	}


	double getSumCost()		// This function is to add up all the prices of the items and store it to the variable finalCost
	{
		current = first;
		if (current == NULL) {
			finalCost = 0;
			return finalCost;
		}
		finalCost = current->info.getCost();
		while (current->link != NULL) {
			current = current->link;	// traverses through the linked list
			finalCost += current->info.getCost();
		}

		return finalCost;
	}


	void sortNode()		// This function sorts the nodes 
	{
		Node* lastItemInOrder;
		Node* firstNotInOrder;
		Node* trailingCurrent;
		Node* currentPtr;

		lastItemInOrder = first;

		while (lastItemInOrder->link != NULL)
		{
			firstNotInOrder = lastItemInOrder->link;

			if (firstNotInOrder->info.getProductName() < first->info.getProductName())
			{
				lastItemInOrder->link = firstNotInOrder->link;
				firstNotInOrder->link = first;
				first = firstNotInOrder;
			}
			else
			{
				trailingCurrent = first;
				currentPtr = first->link;

				while (currentPtr->info.getProductName() < firstNotInOrder->info.getProductName())
				{
					trailingCurrent = currentPtr;
					currentPtr = currentPtr->link;
				}

				if (currentPtr != firstNotInOrder)
				{
					lastItemInOrder->link = firstNotInOrder->link;
					firstNotInOrder->link = currentPtr;
					trailingCurrent->link = firstNotInOrder;
				}
				else
				{
					lastItemInOrder = lastItemInOrder->link;
				}

			}
		}
	}


};



int main(int argc, char* argv[])
{
	NodeList node;
	ArgumentManager am(argc, argv);
	string infilename = am.get("A");
	string outfilename = am.get("C");
	string productName;
	string reader; // reads the entire line 
	string tempCost;
	double budget;
	double price;


	ifstream readFile;
	readFile.open(infilename.c_str());

	string var;
	getline(readFile, var);
	if (var.empty() == true) // If the budget does not exist then it will create a file w/ everything to 0
	{
		ofstream writting(outfilename.c_str());
		node.writeFile(writting);
		writting.close();
		node.printList();
		return 0;
	}

	readFile.seekg(0, ios::beg);  // if the budget does exist then it will start at the beginning of the file

	if (readFile.fail())
	{
		cout << "File not found";
		exit(1);
	}

	readFile >> budget;

	if (readFile.eof()) // if file is empty
	{
		ofstream writting(outfilename.c_str());
		node.writeFile2(writting);
		writting.close();
		return 0;
	}
	readFile.get() != '\n'; // ignores the line that contains buget so I can read the rest of of the lines

	if (budget < 0) { // checks to see if budget is negative to write to the file w/ everything to 0
		ofstream writting(outfilename.c_str());
		node.writeFile2(writting);
		writting.close();
		return 0;
	}



	while (getline(readFile, reader)) // stores the product names into a string
	{
		if (reader.find(',') == -1) { // looking to see if product name doesnt exist to ignore
			continue;
		}

		productName = reader.substr(0, reader.find(',')); // reading and dividing half of the string. 
														  // Begins at the first character of the string, and stops as soon as it reaches the comma
		if (productName == "") // if there is not a product name on the file, ignore it
		{
			continue;
		}
		
		tempCost = reader.substr(reader.find(',') + 1, reader.length() - 1);
		price = stod(tempCost); // converts string to double and stores the cost into budget
		if (price < 0) {
			continue;
		}
	
		node.AddNode(productName, price);

	}

	readFile.close();
	node.sortNode();
	node.getSumCost();


	if (budget < node.findMinCost())
	{
		ofstream writting(outfilename.c_str());
		node.writeFile3(writting);
		writting.close();
		return 0;
	} 

	while (node.finalCost > budget) // deletes the node everytime the total cost of the items exceeds the limit
	{

		node.deleteNode(node.findMaxCost());

	}



	ofstream writting(outfilename.c_str());
	node.writeFile(writting);
	writting.close();
	return 0;






	//system("pause");
	return 0;

}
