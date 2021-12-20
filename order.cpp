#define _CRT_SECURE_NO_WARNINGS   //����Ų���ֱ�����ڵ�һ��,��Ȼû����
#include "order.h"

void order::menu() //һ�е����˵��� 
{
	cout << "***************************************" << endl;
	cout << "*            1.�鿴���ж���           *" << endl;
	cout << "*            2.���Ӷ���               *" << endl;
	cout << "*            3.ɾ������               *" << endl;
	cout << "*            4.�޸Ķ���               *" << endl;
	cout << "*            5.���Ҷ���               *" << endl;
	cout << "*            0.�˳�                   *" << endl;
	cout << "***************************************" << endl;
}
void order::writeToFile(class order* head)  //д�ļ� 
{
	ofstream outfile;
	outfile.open("order_from.txt", ios::out);
	while (head->next != NULL)
	{
		outfile << head->next->ID << '\t';
		outfile << head->next->Date << '\t';
		outfile << head->next->Sname << '\t';
		outfile << head->next->Sphone << '\t'; 
		outfile << head->next->Goods << '\t';
		outfile << head->next->Sarea << '\t';
		outfile << head->next->Rarea << '\t';
		outfile << head->next->Rname << '\t';
		outfile << head->next->Rphone << '\t';
		outfile << head->next->Worker << '\t';
		outfile << head->next->Condition << endl;
		head = head->next;
	}
	outfile.close();
}

int order::readFromFile(class order* head)  //���ļ� 
{
	class order* p;
	p = head;
	ifstream infile;		//�����ļ������,��Щ��Ť,��������ȷ��
	infile.open("order_from.txt", ios::in);//in���ļ�,outд�ļ�
	while (!infile.eof())
	//eof�����ж��Ƿ����һ���ļ������ı�־�����������һ�е����һ������ʱ����ʵҪ�ٶ�һ�β��ܶ����Ǹ���־����ʱ�����ٴν���ѭ��
	{
		order* newnode = new order;
		infile >> newnode->ID;
		if (newnode->ID.length() == 0)//�������һ��Ҫɾ�ˣ�����ѭ��,�Ų�������һ�� 
		{
			delete newnode;
			break;
		}
		infile >> newnode->Date;
		infile >> newnode->Sname;
		infile >> newnode->Sphone;
		infile >> newnode->Goods;
		infile >> newnode->Sarea;
		infile >> newnode->Rarea;
		infile >> newnode->Rname;
		infile >> newnode->Rphone;
		infile >> newnode->Worker;
		infile >> newnode->Condition;
		p->next = newnode;
		p = p->next;
	}
	infile.close();
	return 0;
}

void order::show(class order* head)//�鿴ȫ������ 
{
	while (head->next != NULL)
	{
		cout << "�����ţ�";
		cout << head->next->ID << '\t';
		cout << "ʱ�䣺";
		cout << head->next->Date << '\t';
		cout << "�ļ���������";
		cout << head->next->Sname << '\t';
		cout << "�ļ��˵绰��";
		cout << head->next->Sphone << '\t' << endl;
		cout << "�������ƣ�";
		cout << head->next->Goods << '\t';
		cout << "�����أ�";
		cout << head->next->Sarea << '\t';
		cout << "�ջ��أ�";
		cout << head->next->Rarea << '\t';
		cout << "�ռ���������";
		cout << head->next->Rname << '\t';
		cout << "�ռ��˵绰��";
		cout << head->next->Rphone << '\t' << endl;
		cout << "����Ա��";
		cout << head->next->Worker << '\t';
		cout << "����״̬��";
		cout << head->next->Condition << endl;
		cout << endl;
		head = head->next;
	}
	system("pause");
	system("cls");
}
string GetSystemTime()  //��ȡʱ�亯�� �����Ҷ�������ַ�����ʽ�� 
{
	SYSTEMTIME m_time;   //��Դ��windows.h�ļ�
	GetLocalTime(&m_time);
	char szDateTime[100] = { 0 };
	sprintf(szDateTime, "%02d��%02d��%02d��%02d:%02d:%02d", m_time.wYear, m_time.wMonth,
		m_time.wDay, m_time.wHour, m_time.wMinute, m_time.wSecond);		//sprintf�ڸ�ʽ��ʹ��ʱ��printf����һЩ
	string time(szDateTime);
	return time;
}
void order::add(class order* head)  //���Ӷ��� 
{
	string n;
	order* p = new order;
	order* pr = new order;
	p = head;
	cout << "����������������Ϣ" << endl;
	cout << "������: " << endl;
	cin >> n;
	while (p->next != NULL)
	{
		if (p->ID == n)
		{
			cout << "����Ķ������Ѵ��ڣ����������룺" << endl;
			p = head;
			cin.clear(); //��ջ����� 
			cin.sync();
			cin >> n;
		}
		p = p->next;
	}
	p->next = pr;
	pr->next = NULL;
	pr->ID = n;
	string a;
	a = GetSystemTime();
	pr->Date = a;
	cout << "�ļ�������: " << endl;
	cin >> pr->Sname;
	cout << "�ļ��˵绰��" << endl;
	cin >> pr->Sphone;
	cout << "�������ƣ�" << endl;
	cin >> pr->Goods;
	cout << "�����أ�" << endl;
	cin >> pr->Sarea;
	cout << "�ջ��أ�" << endl;
	cin >> pr->Rarea;
	cout << "�ռ���������" << endl;
	cin >> pr->Rname;
	cout << "�ռ��˵绰��" << endl;
	cin >> pr->Rphone;
	cout << "����Ա��" << endl;
	cin >> pr->Worker;
	cout << "����״̬��" << endl;
	cin >> pr->Condition;
	cout << "���ӳɹ���" << endl;
	system("pause");
	system("cls");
}
void order::coutt(class order* head)
{
	cout << "�����ţ�";
	cout << head->next->ID << '\t';
	cout << "ʱ�䣺";
	cout << head->next->Date << '\t';
	cout << "�ļ���������";
	cout << head->next->Sname << '\t';
	cout << "�ļ��˵绰��";
	cout << head->next->Sphone << '\t' << endl;
	cout << "�������ƣ�";
	cout << head->next->Goods << '\t';
	cout << "�����أ�";
	cout << head->next->Sarea << '\t';
	cout << "�ջ��أ�";
	cout << head->next->Rarea << '\t';
	cout << "�ռ���������";
	cout << head->next->Rname << '\t';
	cout << "�ռ��˵绰��";
	cout << head->next->Rphone << '\t' << endl;
	cout << "����Ա��";
	cout << head->next->Worker << '\t';
	cout << "����״̬��";
	cout << head->next->Condition << endl;
}
void order::Delete(class order* head)
{
	int choose;
	string n;
	cout << "����������ɾ��������:" << endl;
	cin >> n;
	int flag = 0;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			cout << "ȷ��ɾ���ö�����Ϣ�𣿣���������1��" << endl;
			cin >> choose;
			if (choose == 1)
			{//������ɾ������
				order* p1 = head->next;
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
		cout << "û���ҵ��ö�����Ϣ��" << endl;
	}
	system("pause");
	system("cls");
}

void order::findByID(class order* head)
{
	string n;
	int flag = 0;
	cout << "�����붩����:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			coutt(head);
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
void order::findBySarea(class order* head)//������ַ��ѯ
{
	string n;
	int flag = 0;
	cout << "����������﷢����:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->Sarea == n)
		{
			coutt(head);
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}

void order::findByRarea(class order* head)//�ռ���ַ��ѯ
{
	string n;
	int flag = 0;
	cout << "������������ջ���:" << endl;
	cin >> n;
	while (head->next != NULL)
	{
		if (head->next->Rarea == n)
		{
			coutt(head);
			flag++;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
void order::Find(class order* head)		//���Һ����Ĳ˵��͹���ʹ��
{
	int choose;
	cout << "1.���ն����Ų���" << endl;
	cout << "2.���ջ��﷢���ز���(����������)" << endl;
	cout << "3.���ջ����ջ��ز���(����������)" << endl;
	cout << "0.�˳�" << endl;
	cin >> choose;
	while (choose < 0 || choose>3)		//��߽�׳��
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
		findBySarea(head);
		break;
	case 3:
		findByRarea(head);
		break;
	}
	system("pause");
	system("cls");
}

void order::revise(class order* head)
{
	int choose = 0;
	cout << "1.�޸�ȫ��" << endl;
	cout << "2.�޸Ļ�������" << endl;
	cout << "3.�޸ķ�����" << endl;
	cout << "4.�޸��ջ���" << endl;
	cout << "5.�޸��ռ�������" << endl;
	cout << "6.�޸��ռ��˵绰" << endl;
	cout << "0.�˳�" << endl;
	cin >> choose;
	while (!(choose >= 0 && choose <= 6))
	{
		cout << "����������������룺" << endl;
		cin >> choose;
	}
	switch (choose)
	{
	case 1:
		reviseAll(head);
		break;
	case 2:
		reviseGoods(head);
		break;
	case 3:
		reviseSarea(head);
		break;
	case 4:
		reviseRarea(head);
		break;
	case 5:
		reviseRname(head);
		break;
	case 6:
		reviseRphone(head);
		break;
		system("pause");
		system("cls");
	}
}
void order::reviseAll(class order* head)
{
	cout << "����Ҫ�޸Ķ����Ķ����ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)			//��������
	{
		if (temp == head->next->ID)
		{
			cout << "�����»������ƣ�" << endl;
			cin >> n;
			head->next->Goods = n;
			cout << "�����·����أ�" << endl;
			cin >> n;
			head->next->Sarea = n;
			cout << "�������ջ��أ�" << endl;
			cin >> n;
			head->next->Rarea = n;
			cout << "�������ռ���������" << endl;
			cin >> n;
			head->next->Rname = n;
			cout << "�������ռ��˵绰��" << endl;
			cin >> n;
			head->next->Rphone = n;
			cout << "����������Ա��" << endl;
			cin >> n;
			head->next->Worker = n;
			cout << "����������״̬��" << endl;
			cin >> n;
			head->next->Condition = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}

void order::reviseGoods(class order* head)
{
	cout << "����Ҫ�޸Ķ����Ķ����ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "�����»������ƣ�" << endl;
			cin >> n;
			head->next->Goods = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
//�޸ķ�����ַ
void order::reviseSarea(class order* head)
{
	cout << "����Ҫ�޸Ķ����Ķ����ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "�����·����أ�" << endl;
			cin >> n;
			head->next->Sarea = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
//�޸��ջ���ַ
void order::reviseRarea(class order* head)
{
	cout << "����Ҫ�޸Ķ����Ķ����ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "�������ջ��أ�" << endl;
			cin >> n;
			head->next->Rarea = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
//�޸�����
void order::reviseRname(class order* head)
{
	cout << "����Ҫ�޸Ķ����Ķ����ţ�" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "�������ռ���������" << endl;
			cin >> n;
			head->next->Rname = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
//�޸ĵ绰
void order::reviseRphone(class order* head)
{
	cout << "����Ҫ�޸Ķ����Ķ����ţ�" << endl;
	int flag = 0;
	string temp;
	string n;		//����Ҫ�޸ĵ�����
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "�������ռ��˵绰��" << endl;
			cin >> n;
			head->next->Rphone = n;
			cout << "�޸ĳɹ�!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "û���ҵ��ö�����" << endl;
	}
}
