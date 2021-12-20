#pragma once
#include<iostream>
#include<string>   
#define MaxSize 50   //�������Ŀ��Ϊ50,�궨��ĺô����ڿ��Կ��ٶ�ȫ�ֽ��и���
using namespace std;

struct  dat { 
	int start;//��� 
	int end;//�յ� 
	int distance;  //����
};



template <class T>
class Map
{
public:
	Map(T a[], int n);             //���캯������ʼ������n�������ͼ,�����Ǹ�������
	~Map() { }                     //��������Ϊ��
	void EdgeTransform(int start, int end, int distance);//����Ԫ��ת��Ϊ�ڽӾ��� 
	void Print();                       //��ÿ��������� 
	int Dijkstra(int start, int end); //�������·�� 
	int addcity(string city);//��ӳ���
	int deletecity(int city); //ɾ������
	void writeroute(dat*& edge, int& edgenum);//route�ļ���д 
	void DepthSearch(int v, int s[]);//������������ο������������ݽṹP364
	//void BreadthSearch(int v, int s[]);//����������� 
private:
	T  vertex[MaxSize];                    //���ͼ�ж���/���е�����
	int data[MaxSize][MaxSize];             //���ͼ�бߵ�����/���м����
	int nodeNum, edgeNum;                  //ͼ�Ķ������ͱ���
	//void Prim(dat& arr);
};
template <class Type>
class Loading		//ѡ��װ��
{
public:
	void Backtrack(int i);  //�����㷨��װ�ػ�������Ž� 
	int n, //������� 
		* x, //��ǰ��
		* bestx; //��ǰ���Ž�
	Type* w, //������������
		carrying, //��һ��������
		carryweight, //��ǰ������
		bestw, //��ǰ����������
		remain; //ʣ�������
};