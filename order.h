#pragma once			//��ֹͷ�ļ�����ε���,visual�Դ�
#include<iostream>
#include<string>
#include<sstream>
#include<windows.h>		//��ȡʱ��
#include <fstream>
using namespace std;
class order
{
	string ID;  //������� 
	string Date;  //����ʱ��
	string Sname;  //�ļ���
	string Sphone;  //�ļ��˵绰 
	string Goods;  //������
	string Sarea;  //��ʼ�� 
	string Rarea;  //Ŀ�ĵ� 
	string Rname;  //�ռ���
	string Rphone; //�ռ��˵绰 
	string Worker; //����Ա 
	string Condition; //����״̬ 
	class order* next;//����ģʽ����һ��ָ��
private:
public:
	order() :next(NULL) {}
	void writeToFile(class order* head);  //д�ļ� 
	int readFromFile(class order* head);  //���ļ� 
	void menu();  //�˵��� 
	void show(class order* head); //�鿴ȫ������
	void add(class order* head); //���Ӷ���	
	void Delete(class order* head);//ɾ������
	void Find(class order* head);//���Ҷ���
	void findByID(class order* head);//ͨ��id���Ҷ���,���¶������Ʒ���
	void findBySarea(class order* head);
	void findByRarea(class order* head);
	//���¶����޸��õĺ���
	void revise(class order* head);		//���ò˵�
	void reviseAll(class order* head);		//�޸�������Ϣ
	void reviseGoods(class order* head);//�޸���Ʒ��Ϣ
	void reviseSarea(class order* head);//����
	void reviseRarea(class order* head);//�ռ�
	void reviseRname(class order* head);//�ռ�������
	void reviseRphone(class order* head);//�ռ��˵绰����
	void coutt(class order* head);

};


