#define _CRT_SECURE_NO_WARNINGS   //����Ų���ֱ�����ڵ�һ��,��Ȼû����
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>   //�������ñ��������ͷ�ļ�setw�����õ�
#include <string> 
#include "order.h"		//����˵�ϵͳ
#include "city.cpp"
#include "employee.h"
using namespace std;
//���ã����ļ���������ȡ�����Ž������� 
//nodeName ��������    edge ���㼰Ȩֵ
//nodenum ��������	edgenum �ߵ����� 
void getfile(string*& nodeName, dat*& edge, int& nodenum, int& edgenum)
{
	ifstream fcity, froute;
	char f[25];

	//��ȡcity�ļ� 
	strcpy(f, "city.txt");
	fcity.open(f);		//���ļ���ַ����,����ǿ�,�򱨴�
	if (!fcity)
	{
		cout << "�ļ��޷��򿪣������ļ�����" << endl;
	}
	fcity >> nodenum;
	nodeName = new string[MaxSize];
	for (int i = 0; i < nodenum; i++)
	{
		fcity >> nodeName[i];   //���붥����Ϣ
	}
	fcity.close();

	//��ȡroute�ļ�	
	strcpy(f, "route.txt");
	froute.open(f);
	if (!froute)
	{
		cout << "�ļ��޷��򿪣������ļ�����" << endl;
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

//ʵ�ֶ�����ѯ,
int ordermain() 
{
	order* head = new order;
	head->readFromFile(head);

	int t = 1;
	while (t != 0)
	{
		system("cls");
		head->menu();
		cout << "��ѡ��˵���0~5����" << endl;
		cin >> t;
		while (!(t >= 0 && t <= 5))
		{
			cout << "����������������룺" << endl;
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

//���ã���ʾ����Ա���Ľ��� 
int showEmployee()
{
	employee* head = new employee;
	head->readFromFile(head);
	int choice = 1;
	while (choice != 0)
	{
		system("cls");
		head->menu();
		cout << "��ѡ��˵���0~5����" << endl;
		cin >> choice;
		while (!(choice >= 0 && choice <= 5))
		{
			cout << "����������������룺" << endl;
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

//ɾ��·��
void delLine(dat*& edge, int& edgenum, Map<string>& log, int nodnum)
{
	int start00, end00, i;
	cout << "���������:";
	cin >> start00;
	if (start00 <= 0 || start00 > nodnum) throw "������Χ";
	cout << "�������յ�:";
	cin >> end00;
	if (end00 <= 0 || end00 > nodnum) throw "������Χ";
	log.EdgeTransform(start00, end00, 0x3f3f3f3f);//  ����   ��main  ���ļ� 
	for (i = 0; i < edgenum; i++) //�����
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
	//��ʼ��
	string* nodeName;  //�������� 
	dat* edge;		//�ߵ���Ԫ�� 
	//��������б�������ʾ����ȷ,������������֣�Ҫô������data���ֵĵط�ǰ�����ʶ��::��Ҫô��data����,���������ڰѽṹ����������ظ���
	int cnodeNum = 0, edgenum = 0;   //������������ 
	getfile(nodeName, edge, cnodeNum, edgenum);
	Map<string>   mapmap(nodeName, cnodeNum);//������ 
	for (int i = 0; i < edgenum; i++) //�����
	{
		mapmap.EdgeTransform(edge[i].start, edge[i].end, edge[i].distance);
	}

	int syschoose = 0, choose = 0, get = 0, choose1 = 0;
	while (syschoose != 1)
	{
		cout << "����������" << cnodeNum << endl;
		cout << "�������ƣ�" << endl;//cout << "     ";
		for (int i = 1; i <= cnodeNum; i++)
		{
			cout << setw(8) <<  i << "." << nodeName[i - 1] << setiosflags(ios::right) ;    //setw()һ������������ǰ��,��ʾ���ռ��������,�����ÿո���,setiosflags(ios::right)�������Ҷ���
			if (i % 5 == 0) cout << endl;
		}
		cout << endl << "-------��������ϵͳ-------" << endl;
		cout << "���й��ܣ�" << endl;
		cout << "0.���붩������ϵͳ" << endl;
		cout << "1.��������Ա��ϵͳ" << endl;
		cout << "2.��ӳ���" << endl;
		cout << "3.ɾ������" << endl;
		cout << "4.����·��չʾ" << endl;
		cout << "5.�������·��" << endl;
		cout << "6.ɾ������·��" << endl;
		cout << "7.��������" << endl;
		cout << "8.���ͻ����·�����ŷ���" << endl;//����Dijkstra,�ο������ݽṹ���������376ҳ
		//cout << "10.���ͻ����װ�����ŷ���" << endl;
		cout << "9.���ͻ���ķ��ü���" << endl;
		cout << endl << endl;
		cout << "��ѡ��";
		cin >> choose;
		switch (choose)
		{
		case 0://���붩������ϵͳ
			ordermain();
			break;
		case 1://��������Ա��ϵͳ
			showEmployee();
			break;
		case 2://����������,�������Ժӱ�Ϊ��,����������ʯ��ׯ,��ɽ,�ػʵ�,����,��̨,����,�żҿ�,�е�,����,�ȷ�,��ˮ
		{
			cout << "���������Ա����" << endl;
			string mima;
			cin >> mima;
			if (mima != "123456")
				goto there;
			string cityadd;
			int att = 1;		//�����ж��ǿջ����ظ�������,��������޷���bool
			cout << "�������������:";
			cin >> cityadd;
			att = mapmap.addcity(cityadd);
			if (att == 0) break;
			else if (att == 2)
			{
				cout << "��������ظ�����" << endl;
				break;
			}
			else 
			{
				cout << "��ӳ��гɹ�����" << endl;
				nodeName[cnodeNum].append(cityadd);
				cnodeNum++;
				break;
			}
		}
		case 3://ɾ���������
		{
			cout << "���������Ա����" << endl;
			string mima;
			cin >> mima;
			if (mima != "123456")
				goto there;

			int att = 1, citydel;
			cout << "������ɾ�����е����:";
			cin >> citydel;
			att = mapmap.deletecity(citydel);
			if (att == 0)
			{
				cout << "�ļ���ȡʧ�ܣ���" << endl;
				break;
			}
			for (int i = citydel - 1; i < cnodeNum; i++)
			{
				nodeName[i] = nodeName[i + 1];
			}
			cnodeNum--;
			cout << "ɾ�����гɹ�����" << endl;
			break;
		}
		case 4://����·��չʾ
			cout << "-------------------------------------" << endl;
			cout << "|��� |����1    ��   ����2|���루km��|" << endl;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < edgenum; i++)
			{
				//setw()���ÿ��
				cout << "|" << setiosflags(ios::right) << setw(4) << i << " |" << setw(8) << nodeName[edge[i].start - 1] << " ��" <<setw(8)<< nodeName[edge[i].end - 1] << "|    ";
				cout << left << setw(5) << edge[i].distance << endl;
			}
			cout << "-------------------------------------" << endl;
			cout << endl << endl;
			break;
		case 5://�������·��
		{
			cout << "���������:";
			cin >> edge[edgenum].start;
			if (edge[edgenum].start <= 0 || edge[edgenum].start > cnodeNum) throw "������Χ";
			cout << "�������յ�:";
			cin >> edge[edgenum].end;
			if (edge[edgenum].end <= 0 || edge[edgenum].end > cnodeNum) throw "������Χ";
			cout << "������·��:";
			cin >> edge[edgenum].distance;
			if (edge[edgenum].distance <= 0 || edge[edgenum].distance > 10000) throw "������Χ";
			mapmap.EdgeTransform(edge[edgenum].start, edge[edgenum].end, edge[edgenum].distance);
			edgenum++;
			mapmap.writeroute(edge, edgenum);
			break;
		}
		case 6://ɾ������·��
		{
			delLine(edge, edgenum, mapmap, cnodeNum);
			break;
		}
		case 7://��������
			system("cls");
			int v, s[20];
			for (int i = 0; i < cnodeNum; i++)
			{
				s[i] = 0;
				cout << i << "." << nodeName[i] << "	";
				if ((i + 1) % 5 == 0) cout << endl;
			}
			cout << endl<<"���������ʼ��" << endl;
			cin >> v;
			mapmap.DepthSearch(v, s);
			break;
		case 8://���ͻ����·�����ŷ���
			int start, end;
			cout << "���������(����):";
			cin >> start;
			cout << "�������յ�(����):";
			cin >> end;
			mapmap.Dijkstra(start - 1, end - 1);
			break;
		case 9://"9.���ͻ���ĳɱ����ŷ���"
			int start1, end1, routelong;
			double sum;//�ɱ� 
			cout << "���������:";
			cin >> start1;
			cout << "�������յ�:";
			cin >> end1;
			routelong = mapmap.Dijkstra(start1 - 1, end1 - 1);//·������ 
			cout << "���������ػ��������,�����������Ʒ�����븺��" << endl;
			double weight;
			cin >> weight;
			if (0<weight&& weight < 1)//���ù������㷨
			{
				if (routelong < 200)
				{
					sum = routelong * 0.0065 * weight;
					cout << "����С��һǧ��,�������С��200����,��ÿ�ٹ��ﻨ��0.65Ԫ" << endl;
					cout << "�����㣬�ܳɱ�Ϊ��  " << sum << "Ԫ" << endl << endl;
				}
				else
				{
					sum = weight* (200 * 0.0062 + ((double)routelong - 200) * 0.0045);
					cout << "����С��һǧ��,����������200����,200�����ڳ�ÿ�ٹ���ÿǧ�˻���0.6Ԫ,����200���ֳ�ÿ�ٹ���ÿǧ�˻���0.45Ԫ" << endl;
					cout << "�����㣬�ܳɱ�Ϊ��  " << sum << "Ԫ" << endl << endl;
				}
			}
			else if (weight > 1)
			{
				if (routelong < 200)
				{
					sum = routelong * 0.006 * weight;
					cout << "��������һǧ��,�������С��200����,��ÿ�ٹ��ﻨ��0.6Ԫ" << endl;
					cout << "�����㣬�ܳɱ�Ϊ��  " << sum << "Ԫ" << endl << endl;
				}
				else
				{
					sum =- weight * (200 * 0.005 + ((double)routelong - 200) * 0.004);
					cout << "��������һǧ��,����������200����,200�����ڳ�ÿ�ٹ���ÿǧ�˻���0.5Ԫ,����200���ֳ�ÿ�ٹ���ÿǧ�˻���0.4Ԫ" << endl;
					cout << "�����㣬�ܳɱ�Ϊ��  " << sum << "Ԫ" << endl << endl;
				}
			}
			else
			{
				cout << "����Ʒ��������Ʒ,��Ҫ��������,������������Ʒ����" << endl;
				cin >> weight;;
				sum = -weight* routelong * 0.008;
				cout << "�����㣬ÿ�ٹ���ÿǧ����Ҫ�˷�0.8Ԫ,���ܳɱ�Ϊ��  " << sum << "Ԫ" << endl << endl;

			}
			break;
		default:
			cout << "������󣡣�����������" << endl;
			system("pause");
			goto there;
		}
		cout << endl << "�Ƿ�ص������棿��" << endl << "1.��  2.��" << endl;
		cin >> get;
		if (get == 2)
			syschoose = 1;
		else
			syschoose = 0;
	there://goto ���ĵ����,����һ����ǩ
		system("cls");
	}
	return 0;
}