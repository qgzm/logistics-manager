#include"employee.h"
#include <iostream>
#include<fstream>
using namespace std;

void employee::menu()
{
	cout << "***************************************" << endl;
	cout << "*                                     *" << endl;
	cout << "*            1.查看所有员工           *" << endl;
	cout << "*            2.增加员工信息           *" << endl;
	cout << "*            3.删除员工信息           *" << endl;
	cout << "*            4.修改员工信息           *" << endl;
	cout << "*            5.查找员工信息           *" << endl;
	cout << "*            0.退出                   *" << endl;
	cout << "*                                     *" << endl;
	cout << "***************************************" << endl;
}

void employee::Find(class employee* head)
{
	int choose;
	cout << "1.按照工号查找" << endl;
	cout << "2.按照名字查找" << endl;
	cout << "3.按照电话查找" << endl;
	cin >> choose;
	while (choose < 1 || choose>3)
	{
		cout << "输入错误，请重新输入：" << endl;
		cin >> choose;
	}
	switch (choose)
	{
	case 1:
		findByID(head);
		break;
	case 2:
		findByName(head);
		break;
	case 3:
		findByNumber(head);
		break;
	}
	system("pause");
	system("cls");
}

void employee::findByID(class employee* head)
{
	string n;
	int flag = 0;
	cout << "请输入员工工号:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			cout << "工号：";
			cout << head->next->ID << '\t';
			cout << "名字：";
			cout << head->next->name << '\t';
			cout << "电话：";
			cout << head->next->number<< endl;
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
}

void employee::findByName(class employee* head)
{
	string n;
	int flag = 0;
	cout << "请请输入员工名字:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->name == n)
		{
			cout << "工号：";
			cout << head->next->ID << '\t';
			cout << "名字：";
			cout << head->next->name << '\t';
			cout << "电话：";
			cout << head->next->number << endl;
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
}

void employee::findByNumber(class employee* head)
{
	string n;
	int flag = 0;
	cout << "请请输入员工电话:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->number == n)
		{
			cout << "工号：";
			cout << head->next->ID << '\t';
			cout << "名字：";
			cout << head->next->name << '\t';
			cout << "电话：";
			cout << head->next->number << endl;
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
}

void employee::Delete(class employee* head)
{
	int choose;
	string n;
	cout << "请输入你想删除员工工号:" << endl;
	cin >> n;
	int flag = 0;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			cout << "确认删除该员工信息吗？（是请输入1）" << endl;
			cin >> choose;
			if (choose == 1)
			{
				employee* p1 = head->next;
				head->next = head->next->next;
				delete p1;
				p1 = NULL;
				cout << "删除完毕！" << endl;
				flag++;
				break;
			}
			else
			{
				cout << "已取消操作！" << endl;
				flag++;
				break;
			}
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
	system("pause");
	system("cls");
}

void employee::add(class employee* head)
{
	string n;
	employee* p = new employee;
	employee* pr = new employee;
	p = head;
	cout << "请输入员工信息" << endl;
	cout << "工号: " << endl;
	cin >> n;
	while (p->next != NULL)
	{
		if (p->ID == n)
		{
			cout << "输入工号重复,即将退出！" << endl;
			exit(1);
		}
		p = p->next;
	}
	p->next = pr;
	pr->next = NULL;
	pr->ID = n;
	cout << "姓名: " << endl;
	cin >> pr->name;
	cout << "电话: " << endl;
	cin >> pr->number;
	system("pause");
	system("cls");
}

int employee::readFromFile(class employee* head)
{
	class employee* p;
	p = head;
	ifstream infile;
	infile.open("工人.txt", ios::in);
	while (!infile.eof())//eof就是判断是否读到一个文件结束的标志，当读到最后一行的最后一个数的时候，其实要再读一次才能读到那个标志，这时程序再次进入循环
	{
		employee* newnode = new employee;
		infile >> newnode->ID;
		if (newnode->ID.length() == 0)//所以最后一次要删了，跳出循环,才不会最后多一行 
		{
			delete newnode;
			break;
		}
		infile >> newnode->name;
		infile >> newnode->number;
		p->next = newnode;
		p = p->next;
	}
	infile.close();
	return 0;
}

void employee::revise(class employee* head)
{
	int choose = 0;
	cout << "1.修改员工名字" << endl;
	cout << "2.修改员工电话" << endl;
	cout << "3.修改全部" << endl;
	cin >> choose;
	while (!(choose >= 1 && choose <= 3))
	{
		cout << "输入错误，请重新输入：" << endl;
		cin >> choose;
	}
	switch (choose)
	{
	case 1:
		reviseName(head);
		break;
	case 2:
		reviseNumber(head);
		break;
	case 3:
		reviseAll(head);
		break;
	}
	system("pause");
	system("cls");
}

void employee::reviseName(class employee* head)
{
	cout << "输入要修改员工的工号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新名字：" << endl;
			cin >> n;
			head->next->name = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
}

void employee::reviseNumber(class employee* head)
{
	cout << "输入要修改员工的工号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新电话：" << endl;
			cin >> n;
			head->next->number = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
}


void employee::reviseAll(class employee* head)
{
	cout << "输入要修改员工的工号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新名字：" << endl;
			cin >> n;
			head->next->name = n;
			cout << "输入新电话：" << endl;
			cin >> n;
			head->next->number = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该员工！" << endl;
	}
}


void employee::show(class employee* head)
{
	while (head->next != NULL)
	{
		cout << "工号：";
		cout << head->next->ID << '\t';
		cout << "名字：";
		cout << head->next->name << '\t';
		cout << "电话：";
		cout << head->next->number << endl;
		head = head->next;
	}
	system("pause");
	system("cls");
}


void employee::writeToFile(class employee* head)
{
	ofstream outfile;
	outfile.open("工人.txt", ios::out);
	while (head->next != NULL)
	{
		outfile << head->next->ID << '\t';
		outfile << head->next->name << '\t';
		outfile << head->next->number << endl;
		head = head->next;
	}
	outfile.close();
}