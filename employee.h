#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include <fstream>
using namespace std;
class employee
{
private:
	string ID;
	string number;
	string name;
	class employee* next;
public:
	employee() :next(NULL) {}
	int readFromFile(class employee* head);
	void writeToFile(class employee* head);
	void menu();

	void add(class employee* head);

	void Find(class employee* head);
	void findByName(class employee* head);
	void findByID(class employee* head);
	void findByNumber(class employee* head);

	void Delete(class employee* head);

	void show(class employee* head);

	void revise(class employee* head);
	void reviseName(class employee* head);
	void reviseNumber(class employee* head);
	void reviseAll(class employee* head);
};