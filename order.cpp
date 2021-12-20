#define _CRT_SECURE_NO_WARNINGS   //多次排查后发现必须放在第一行,不然没有用
#include "order.h"

void order::menu() //一中的主菜单栏 
{
	cout << "***************************************" << endl;
	cout << "*            1.查看所有订单           *" << endl;
	cout << "*            2.增加订单               *" << endl;
	cout << "*            3.删除订单               *" << endl;
	cout << "*            4.修改订单               *" << endl;
	cout << "*            5.查找订单               *" << endl;
	cout << "*            0.退出                   *" << endl;
	cout << "***************************************" << endl;
}
void order::writeToFile(class order* head)  //写文件 
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

int order::readFromFile(class order* head)  //读文件 
{
	class order* p;
	p = head;
	ifstream infile;		//创建文件输出流,有些别扭,但是是正确的
	infile.open("order_from.txt", ios::in);//in读文件,out写文件
	while (!infile.eof())
	//eof就是判断是否读到一个文件结束的标志，当读到最后一行的最后一个数的时候，其实要再读一次才能读到那个标志，这时程序再次进入循环
	{
		order* newnode = new order;
		infile >> newnode->ID;
		if (newnode->ID.length() == 0)//所以最后一次要删了，跳出循环,才不会最后多一行 
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

void order::show(class order* head)//查看全部订单 
{
	while (head->next != NULL)
	{
		cout << "订单号：";
		cout << head->next->ID << '\t';
		cout << "时间：";
		cout << head->next->Date << '\t';
		cout << "寄件人姓名：";
		cout << head->next->Sname << '\t';
		cout << "寄件人电话：";
		cout << head->next->Sphone << '\t' << endl;
		cout << "货物名称：";
		cout << head->next->Goods << '\t';
		cout << "发货地：";
		cout << head->next->Sarea << '\t';
		cout << "收货地：";
		cout << head->next->Rarea << '\t';
		cout << "收件人姓名：";
		cout << head->next->Rname << '\t';
		cout << "收件人电话：";
		cout << head->next->Rphone << '\t' << endl;
		cout << "配送员：";
		cout << head->next->Worker << '\t';
		cout << "运输状态：";
		cout << head->next->Condition << endl;
		cout << endl;
		head = head->next;
	}
	system("pause");
	system("cls");
}
string GetSystemTime()  //获取时间函数 ，并且对其进行字符串格式化 
{
	SYSTEMTIME m_time;   //来源于windows.h文件
	GetLocalTime(&m_time);
	char szDateTime[100] = { 0 };
	sprintf(szDateTime, "%02d年%02d月%02d日%02d:%02d:%02d", m_time.wYear, m_time.wMonth,
		m_time.wDay, m_time.wHour, m_time.wMinute, m_time.wSecond);		//sprintf在格式化使用时比printf好用一些
	string time(szDateTime);
	return time;
}
void order::add(class order* head)  //增加订单 
{
	string n;
	order* p = new order;
	order* pr = new order;
	p = head;
	cout << "请输入新增订单信息" << endl;
	cout << "订单号: " << endl;
	cin >> n;
	while (p->next != NULL)
	{
		if (p->ID == n)
		{
			cout << "输入的订单号已存在，请重新输入：" << endl;
			p = head;
			cin.clear(); //清空缓冲区 
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
	cout << "寄件人姓名: " << endl;
	cin >> pr->Sname;
	cout << "寄件人电话：" << endl;
	cin >> pr->Sphone;
	cout << "货物名称：" << endl;
	cin >> pr->Goods;
	cout << "发货地：" << endl;
	cin >> pr->Sarea;
	cout << "收货地：" << endl;
	cin >> pr->Rarea;
	cout << "收件人姓名：" << endl;
	cin >> pr->Rname;
	cout << "收件人电话：" << endl;
	cin >> pr->Rphone;
	cout << "配送员：" << endl;
	cin >> pr->Worker;
	cout << "运输状态：" << endl;
	cin >> pr->Condition;
	cout << "增加成功！" << endl;
	system("pause");
	system("cls");
}
void order::coutt(class order* head)
{
	cout << "订单号：";
	cout << head->next->ID << '\t';
	cout << "时间：";
	cout << head->next->Date << '\t';
	cout << "寄件人姓名：";
	cout << head->next->Sname << '\t';
	cout << "寄件人电话：";
	cout << head->next->Sphone << '\t' << endl;
	cout << "货物名称：";
	cout << head->next->Goods << '\t';
	cout << "发货地：";
	cout << head->next->Sarea << '\t';
	cout << "收货地：";
	cout << head->next->Rarea << '\t';
	cout << "收件人姓名：";
	cout << head->next->Rname << '\t';
	cout << "收件人电话：";
	cout << head->next->Rphone << '\t' << endl;
	cout << "配送员：";
	cout << head->next->Worker << '\t';
	cout << "运输状态：";
	cout << head->next->Condition << endl;
}
void order::Delete(class order* head)
{
	int choose;
	string n;
	cout << "请输入你想删除订单号:" << endl;
	cin >> n;
	int flag = 0;
	while (head->next != NULL)
	{
		if (head->next->ID == n)
		{
			cout << "确认删除该订单信息吗？（是请输入1）" << endl;
			cin >> choose;
			if (choose == 1)
			{//链表常规删除操作
				order* p1 = head->next;
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
		cout << "没有找到该订单信息！" << endl;
	}
	system("pause");
	system("cls");
}

void order::findByID(class order* head)
{
	string n;
	int flag = 0;
	cout << "请输入订单号:" << endl;
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
		cout << "没有找到该订单！" << endl;
	}
}
void order::findBySarea(class order* head)//发件地址查询
{
	string n;
	int flag = 0;
	cout << "请请输入货物发货地:" << endl;
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
		cout << "没有找到该订单！" << endl;
	}
}

void order::findByRarea(class order* head)//收件地址查询
{
	string n;
	int flag = 0;
	cout << "请请输入货物收货地:" << endl;
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
		cout << "没有找到该订单！" << endl;
	}
}
void order::Find(class order* head)		//查找函数的菜单和功能使用
{
	int choose;
	cout << "1.按照订单号查找" << endl;
	cout << "2.按照货物发货地查找(请输入数字)" << endl;
	cout << "3.按照货物收货地查找(请输入数字)" << endl;
	cout << "0.退出" << endl;
	cin >> choose;
	while (choose < 0 || choose>3)		//提高健壮性
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
	cout << "1.修改全部" << endl;
	cout << "2.修改货物名称" << endl;
	cout << "3.修改发货地" << endl;
	cout << "4.修改收货地" << endl;
	cout << "5.修改收件人姓名" << endl;
	cout << "6.修改收件人电话" << endl;
	cout << "0.退出" << endl;
	cin >> choose;
	while (!(choose >= 0 && choose <= 6))
	{
		cout << "输入错误，请重新输入：" << endl;
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
	cout << "输入要修改订单的订单号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)			//遍历链表
	{
		if (temp == head->next->ID)
		{
			cout << "输入新货物名称：" << endl;
			cin >> n;
			head->next->Goods = n;
			cout << "输入新发货地：" << endl;
			cin >> n;
			head->next->Sarea = n;
			cout << "输入新收货地：" << endl;
			cin >> n;
			head->next->Rarea = n;
			cout << "输入新收件人姓名：" << endl;
			cin >> n;
			head->next->Rname = n;
			cout << "输入新收件人电话：" << endl;
			cin >> n;
			head->next->Rphone = n;
			cout << "输入新配送员：" << endl;
			cin >> n;
			head->next->Worker = n;
			cout << "输入新运输状态：" << endl;
			cin >> n;
			head->next->Condition = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该订单！" << endl;
	}
}

void order::reviseGoods(class order* head)
{
	cout << "输入要修改订单的订单号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新货物名称：" << endl;
			cin >> n;
			head->next->Goods = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该订单！" << endl;
	}
}
//修改发货地址
void order::reviseSarea(class order* head)
{
	cout << "输入要修改订单的订单号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新发货地：" << endl;
			cin >> n;
			head->next->Sarea = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该订单！" << endl;
	}
}
//修改收货地址
void order::reviseRarea(class order* head)
{
	cout << "输入要修改订单的订单号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新收货地：" << endl;
			cin >> n;
			head->next->Rarea = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该订单！" << endl;
	}
}
//修改姓名
void order::reviseRname(class order* head)
{
	cout << "输入要修改订单的订单号：" << endl;
	int flag = 0;
	string temp;
	string n;
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新收件人姓名：" << endl;
			cin >> n;
			head->next->Rname = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该订单！" << endl;
	}
}
//修改电话
void order::reviseRphone(class order* head)
{
	cout << "输入要修改订单的订单号：" << endl;
	int flag = 0;
	string temp;
	string n;		//接受要修改的内容
	cin >> temp;
	while (head->next != NULL)
	{
		if (temp == head->next->ID)
		{
			cout << "输入新收件人电话：" << endl;
			cin >> n;
			head->next->Rphone = n;
			cout << "修改成功!" << endl;
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cout << "没有找到该订单！" << endl;
	}
}
