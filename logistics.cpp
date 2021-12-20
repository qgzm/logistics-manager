#define _CRT_SECURE_NO_WARNINGS   //多次排查后发现必须放在第一行,不然没有用
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>   //精度设置必须包括的头文件setw函数用到
#include <string> 
#include "order.h"		//导入菜单系统
#include "city.cpp"
#include "employee.h"
using namespace std;
//作用：将文件的内容提取出来放进变量中 
//nodeName 顶点数组    edge 两点及权值
//nodenum 顶点数量	edgenum 边的数量 
void getfile(string*& nodeName, dat*& edge, int& nodenum, int& edgenum)
{
	ifstream fcity, froute;
	char f[25];

	//读取city文件 
	strcpy(f, "city.txt");
	fcity.open(f);		//将文件地址读入,如果是空,则报错
	if (!fcity)
	{
		cout << "文件无法打开，请检查文件再试" << endl;
	}
	fcity >> nodenum;
	nodeName = new string[MaxSize];
	for (int i = 0; i < nodenum; i++)
	{
		fcity >> nodeName[i];   //读入顶点信息
	}
	fcity.close();

	//读取route文件	
	strcpy(f, "route.txt");
	froute.open(f);
	if (!froute)
	{
		cout << "文件无法打开，请检查文件再试" << endl;
	}
	froute >> edgenum;
	edge = new dat[MaxSize];
	for (int i = 0; i < edgenum; i++)
	{
		froute >> edge[i].start;
		froute >> edge[i].end;
		froute >> edge[i].distance;
	}
	froute.close();
}

//实现订单查询,
int ordermain() 
{
	order* head = new order;
	head->readFromFile(head);

	int t = 1;
	while (t != 0)
	{
		system("cls");
		head->menu();
		cout << "请选择菜单（0~5）：" << endl;
		cin >> t;
		while (!(t >= 0 && t <= 5))
		{
			cout << "输入错误，请重新输入：" << endl;
			cin >> t;
		}
		switch (t)
		{
		case 1:
			head->show(head);
			break;
		case 2:
			head->add(head);
			head->writeToFile(head);
			break;
		case 3:
			head->Delete(head);
			head->writeToFile(head);
			break;
		case 4:
			head->revise(head);
			head->writeToFile(head);
			break;
		case 5:
			head->Find(head);
			break;
		}
	}
	return 0;
}

//作用：显示运输员工的界面 
int showEmployee()
{
	employee* head = new employee;
	head->readFromFile(head);
	int choice = 1;
	while (choice != 0)
	{
		system("cls");
		head->menu();
		cout << "请选择菜单（0~5）：" << endl;
		cin >> choice;
		while (!(choice >= 0 && choice <= 5))
		{
			cout << "输入错误，请重新输入：" << endl;
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			head->show(head);
			head->writeToFile(head);
			break;
		case 2:
			head->add(head);
			head->writeToFile(head);
			break;
		case 3:
			head->Delete(head);
			head->writeToFile(head);
			break;
		case 4:
			head->revise(head);
			head->writeToFile(head);
			break;
		case 5:
			head->Find(head);
			head->writeToFile(head);
			break;
		}
	}
	return 0;
}

//删除路线
void delLine(dat*& edge, int& edgenum, Map<string>& log, int nodnum)
{
	int start00, end00, i;
	cout << "请输入起点:";
	cin >> start00;
	if (start00 <= 0 || start00 > nodnum) throw "超出范围";
	cout << "请输入终点:";
	cin >> end00;
	if (end00 <= 0 || end00 > nodnum) throw "超出范围";
	log.EdgeTransform(start00, end00, 0x3f3f3f3f);//  改类   改main  改文件 
	for (i = 0; i < edgenum; i++) //插入边
	{
		if (start00 == edge[i].start && end00 == edge[i].end) break;
		if (end00 == edge[i].start && start00 == edge[i].end) break;
	}
	for (int j = i; j < edgenum; j++)
	{
		edge[j].start = edge[j + 1].start;
		edge[j].end = edge[j + 1].end;
		edge[j].distance = edge[j + 1].distance;
	}
	edgenum--;
	log.writeroute(edge, edgenum);
}

int main()
{
	//初始化
	string* nodeName;  //顶点名称 
	dat* edge;		//边的三元组 
	//编译过程中编译器显示不明确,解决方案有两种，要么在所有data出现的地方前加域标识符::，要么给data改名,笔者问题在把结构体和数组名重复了
	int cnodeNum = 0, edgenum = 0;   //顶点数，边数 
	getfile(nodeName, edge, cnodeNum, edgenum);
	Map<string>   mapmap(nodeName, cnodeNum);//创建类 
	for (int i = 0; i < edgenum; i++) //插入边
	{
		mapmap.EdgeTransform(edge[i].start, edge[i].end, edge[i].distance);
	}

	int syschoose = 0, choose = 0, get = 0, choose1 = 0;
	while (syschoose != 1)
	{
		cout << "城市数量：" << cnodeNum << endl;
		cout << "城市名称：" << endl;//cout << "     ";
		for (int i = 1; i <= cnodeNum; i++)
		{
			cout << setw(8) <<  i << "." << nodeName[i - 1] << setiosflags(ios::right) ;    //setw()一般放在输出内容前面,表示输出占几个格子,不足用空格补足,setiosflags(ios::right)控制左右对齐
			if (i % 5 == 0) cout << endl;
		}
		cout << endl << "-------物流管理系统-------" << endl;
		cout << "所有功能：" << endl;
		cout << "0.进入订单管理系统" << endl;
		cout << "1.进入物流员工系统" << endl;
		cout << "2.添加城市" << endl;
		cout << "3.删除城市" << endl;
		cout << "4.城市路线展示" << endl;
		cout << "5.添加运输路线" << endl;
		cout << "6.删除运输路线" << endl;
		cout << "7.遍历城市" << endl;
		cout << "8.运送货物的路径最优方案" << endl;//采用Dijkstra,参考书数据结构殷人昆版第376页
		//cout << "10.运送货物的装载最优方案" << endl;
		cout << "9.运送货物的费用计算" << endl;
		cout << endl << endl;
		cout << "请选择：";
		cin >> choose;
		switch (choose)
		{
		case 0://进入订单管理系统
			ordermain();
			break;
		case 1://进入物流员工系统
			showEmployee();
			break;
		case 2://添加运输城市,本案例以河北为例,包括城市有石家庄,唐山,秦皇岛,邯郸,邢台,保定,张家口,承德,沧州,廊坊,衡水
		{
			cout << "请输入管理员密码" << endl;
			string mima;
			cin >> mima;
			if (mima != "123456")
				goto there;
			string cityadd;
			int att = 1;		//用以判断是空还是重复还是新,三种情况无法用bool
			cout << "请输入城市名字:";
			cin >> cityadd;
			att = mapmap.addcity(cityadd);
			if (att == 0) break;
			else if (att == 2)
			{
				cout << "输入城市重复！！" << endl;
				break;
			}
			else 
			{
				cout << "添加城市成功！！" << endl;
				nodeName[cnodeNum].append(cityadd);
				cnodeNum++;
				break;
			}
		}
		case 3://删除运输城市
		{
			cout << "请输入管理员密码" << endl;
			string mima;
			cin >> mima;
			if (mima != "123456")
				goto there;

			int att = 1, citydel;
			cout << "请输入删除城市的序号:";
			cin >> citydel;
			att = mapmap.deletecity(citydel);
			if (att == 0)
			{
				cout << "文件读取失败！！" << endl;
				break;
			}
			for (int i = citydel - 1; i < cnodeNum; i++)
			{
				nodeName[i] = nodeName[i + 1];
			}
			cnodeNum--;
			cout << "删除城市成功！！" << endl;
			break;
		}
		case 4://城市路线展示
			cout << "-------------------------------------" << endl;
			cout << "|序号 |城市1    到   城市2|距离（km）|" << endl;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < edgenum; i++)
			{
				//setw()设置宽度
				cout << "|" << setiosflags(ios::right) << setw(4) << i << " |" << setw(8) << nodeName[edge[i].start - 1] << " 到" <<setw(8)<< nodeName[edge[i].end - 1] << "|    ";
				cout << left << setw(5) << edge[i].distance << endl;
			}
			cout << "-------------------------------------" << endl;
			cout << endl << endl;
			break;
		case 5://添加运输路线
		{
			cout << "请输入起点:";
			cin >> edge[edgenum].start;
			if (edge[edgenum].start <= 0 || edge[edgenum].start > cnodeNum) throw "超出范围";
			cout << "请输入终点:";
			cin >> edge[edgenum].end;
			if (edge[edgenum].end <= 0 || edge[edgenum].end > cnodeNum) throw "超出范围";
			cout << "请输入路程:";
			cin >> edge[edgenum].distance;
			if (edge[edgenum].distance <= 0 || edge[edgenum].distance > 10000) throw "超出范围";
			mapmap.EdgeTransform(edge[edgenum].start, edge[edgenum].end, edge[edgenum].distance);
			edgenum++;
			mapmap.writeroute(edge, edgenum);
			break;
		}
		case 6://删除运输路线
		{
			delLine(edge, edgenum, mapmap, cnodeNum);
			break;
		}
		case 7://遍历城市
			system("cls");
			int v, s[20];
			for (int i = 0; i < cnodeNum; i++)
			{
				s[i] = 0;
				cout << i << "." << nodeName[i] << "	";
				if ((i + 1) % 5 == 0) cout << endl;
			}
			cout << endl<<"输入遍历起始点" << endl;
			cin >> v;
			mapmap.DepthSearch(v, s);
			break;
		case 8://运送货物的路径最优方案
			int start, end;
			cout << "请输入起点(数字):";
			cin >> start;
			cout << "请输入终点(数字):";
			cin >> end;
			mapmap.Dijkstra(start - 1, end - 1);
			break;
		case 9://"9.运送货物的成本最优方案"
			int start1, end1, routelong;
			double sum;//成本 
			cout << "请输入起点:";
			cin >> start1;
			cout << "请输入终点:";
			cin >> end1;
			routelong = mapmap.Dijkstra(start1 - 1, end1 - 1);//路径长度 
			cout << "请输入运载货物的重量,如果是特殊物品请输入负数" << endl;
			double weight;
			cin >> weight;
			if (0<weight&& weight < 1)//采用哈夫曼算法
			{
				if (routelong < 200)
				{
					sum = routelong * 0.0065 * weight;
					cout << "重量小于一千克,运输距离小于200公里,车每百公里花费0.65元" << endl;
					cout << "经计算，总成本为：  " << sum << "元" << endl << endl;
				}
				else
				{
					sum = weight* (200 * 0.0062 + ((double)routelong - 200) * 0.0045);
					cout << "重量小于一千克,运输距离大于200公里,200公里内车每百公里每千克花费0.6元,大于200部分车每百公里每千克花费0.45元" << endl;
					cout << "经计算，总成本为：  " << sum << "元" << endl << endl;
				}
			}
			else if (weight > 1)
			{
				if (routelong < 200)
				{
					sum = routelong * 0.006 * weight;
					cout << "重量大于一千克,运输距离小于200公里,车每百公里花费0.6元" << endl;
					cout << "经计算，总成本为：  " << sum << "元" << endl << endl;
				}
				else
				{
					sum =- weight * (200 * 0.005 + ((double)routelong - 200) * 0.004);
					cout << "重量大于一千克,运输距离大于200公里,200公里内车每百公里每千克花费0.5元,大于200部分车每百公里每千克花费0.4元" << endl;
					cout << "经计算，总成本为：  " << sum << "元" << endl << endl;
				}
			}
			else
			{
				cout << "该物品是特殊物品,需要特殊运输,请重新输入物品重量" << endl;
				cin >> weight;;
				sum = -weight* routelong * 0.008;
				cout << "经计算，每百公里每千克需要运费0.8元,则总成本为：  " << sum << "元" << endl << endl;

			}
			break;
		default:
			cout << "输入错误！！请重新输入" << endl;
			system("pause");
			goto there;
		}
		cout << endl << "是否回到主界面？？" << endl << "1.是  2.否" << endl;
		cin >> get;
		if (get == 2)
			syschoose = 1;
		else
			syschoose = 0;
	there://goto 语句的到达地,这是一个标签
		system("cls");
	}
	return 0;
}