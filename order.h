#pragma once			//防止头文件被多次调用,visual自带
#include<iostream>
#include<string>
#include<sstream>
#include<windows.h>		//获取时间
#include <fstream>
using namespace std;
class order
{
	string ID;  //订单编号 
	string Date;  //创建时间
	string Sname;  //寄件人
	string Sphone;  //寄件人电话 
	string Goods;  //货物名
	string Sarea;  //起始地 
	string Rarea;  //目的地 
	string Rname;  //收件人
	string Rphone; //收件人电话 
	string Worker; //配送员 
	string Condition; //订单状态 
	class order* next;//链表模式的下一个指针
private:
public:
	order() :next(NULL) {}
	void writeToFile(class order* head);  //写文件 
	int readFromFile(class order* head);  //读文件 
	void menu();  //菜单栏 
	void show(class order* head); //查看全部订单
	void add(class order* head); //增加订单	
	void Delete(class order* head);//删除订单
	void Find(class order* head);//查找订单
	void findByID(class order* head);//通过id查找订单,以下都是类似方法
	void findBySarea(class order* head);
	void findByRarea(class order* head);
	//以下都是修改用的函数
	void revise(class order* head);		//调用菜单
	void reviseAll(class order* head);		//修改所有信息
	void reviseGoods(class order* head);//修改商品信息
	void reviseSarea(class order* head);//发件
	void reviseRarea(class order* head);//收件
	void reviseRname(class order* head);//收件人姓名
	void reviseRphone(class order* head);//收件人电话号码
	void coutt(class order* head);

};


