#include"employee.h"
#include <iostream>
#include<fstream>
using namespace std;

void employee::menu()
{
	cout << "***************************************" << endl;
	cout << "*                                     *" << endl;
	cout << "*            1.�鿴����Ա��           *" << endl;
	cout << "*            2.����Ա����Ϣ           *" << endl;
	cout << "*            3.ɾ��Ա����Ϣ           *" << endl;
	cout << "*            4.�޸�Ա����Ϣ           *" << endl;
	cout << "*            5.����Ա����Ϣ           *" << endl;
	cout << "*            0.�˳�                   *" << endl;
	cout << "*                                     *" << endl;
	cout << "***************************************" << endl;
}

void employee::Find(class employee* head)
{
	int choose;
	cout << "1.���չ��Ų���" << endl;
	cout << "2.�������ֲ���" << endl;
	cout << "3.���յ绰����" << endl;
	cin >> choose;
	while (choose < 1 || choose>3)
	{
		cout << "����������������룺" << endl;
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
	cout << "������Ա������:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			cout << "���ţ�";
			cout << head->next->ID << '\t';
			cout << "���֣�";
			cout << head->next->name << '\t';
			cout << "�绰��";
			cout << head->next->number<< endl;
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
	}
}

void employee::findByName(class employee* head)
{
	string n;
	int flag = 0;
	cout << "��������Ա������:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->name == n)
		{
			cout << "���ţ�";
			cout << head->next->ID << '\t';
			cout << "���֣�";
			cout << head->next->name << '\t';
			cout << "�绰��";
			cout << head->next->number << endl;
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
	}
}

void employee::findByNumber(class employee* head)
{
	string n;
	int flag = 0;
	cout << "��������Ա���绰:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->number == n)
		{
			cout << "���ţ�";
			cout << head->next->ID << '\t';
			cout << "���֣�";
			cout << head->next->name << '\t';
			cout << "�绰��";
			cout << head->next->number << endl;
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
	}
}

void employee::Delete(class employee* head)
{
	int choose;
	string n;
	cout << "����������ɾ��Ա������:" << endl;
	cin >> n;
	int flag = 0;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			cout << "ȷ��ɾ����Ա����Ϣ�𣿣���������1��" << endl;
			cin >> choose;
			if (choose == 1)
			{
				employee* p1 = head->next;
				head->next = head->next->next;
				delete p1;
				p1 = NULL;
				cout << "ɾ����ϣ�" << endl;
				flag++;
				break;
			}
			else
			{
				cout << "��ȡ��������" << endl;
				flag++;
				break;
			}
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
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
	cout << "������Ա����Ϣ" << endl;
	cout << "����: " << endl;
	cin >> n;
	while (p->next != NULL)
	{
		if (p->ID == n)
		{
			cout << "���빤���ظ�,�����˳���" << endl;
			exit(1);
		}
		p = p->next;
	}
	p->next = pr;
	pr->next = NULL;
	pr->ID = n;
	cout << "����: " << endl;
	cin >> pr->name;
	cout << "�绰: " << endl;
	cin >> pr->number;
	system("pause");
	system("cls");
}

int employee::readFromFile(class employee* head)
{
	class employee* p;
	p = head;
	ifstream infile;
	infile.open("����.txt", ios::in);
	while (!infile.eof())//eof�����ж��Ƿ����һ���ļ������ı�־�����������һ�е����һ������ʱ����ʵҪ�ٶ�һ�β��ܶ����Ǹ���־����ʱ�����ٴν���ѭ��
	{
		employee* newnode = new employee;
		infile >> newnode->ID;
		if (newnode->ID.length() == 0)//�������һ��Ҫɾ�ˣ�����ѭ��,�Ų�������һ�� 
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
	cout << "1.�޸�Ա������" << endl;
	cout << "2.�޸�Ա���绰" << endl;
	cout << "3.�޸�ȫ��" << endl;
	cin >> choose;
	while (!(choose >= 1 && choose <= 3))
	{
		cout << "����������������룺" << endl;
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
	cout << "����Ҫ�޸�Ա���Ĺ��ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "���������֣�" << endl;
			cin >> n;
			head->next->name = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
	}
}

void employee::reviseNumber(class employee* head)
{
	cout << "����Ҫ�޸�Ա���Ĺ��ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "�����µ绰��" << endl;
			cin >> n;
			head->next->number = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
	}
}


void employee::reviseAll(class employee* head)
{
	cout << "����Ҫ�޸�Ա���Ĺ��ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "���������֣�" << endl;
			cin >> n;
			head->next->name = n;
			cout << "�����µ绰��" << endl;
			cin >> n;
			head->next->number = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ���Ա����" << endl;
	}
}


void employee::show(class employee* head)
{
	while (head->next != NULL)
	{
		cout << "���ţ�";
		cout << head->next->ID << '\t';
		cout << "���֣�";
		cout << head->next->name << '\t';
		cout << "�绰��";
		cout << head->next->number << endl;
		head = head->next;
	}
	system("pause");
	system("cls");
}


void employee::writeToFile(class employee* head)
{
	ofstream outfile;
	outfile.open("����.txt", ios::out);
	while (head->next != NULL)
	{
		outfile << head->next->ID << '\t';
		outfile << head->next->name << '\t';
		outfile << head->next->number << endl;
		head = head->next;
	}
	outfile.close();
}