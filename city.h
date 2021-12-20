#pragma once
#include<iostream>
#include<string>   
#define MaxSize 50   //将最多数目定为50,宏定义的好处在于可以快速对全局进行更改
using namespace std;

struct  dat { 
	int start;//起点 
	int end;//终点 
	int distance;  //距离
};



template <class T>
class Map
{
public:
	Map(T a[], int n);             //构造函数，初始化具有n个顶点的图,结点就是各个城市
	~Map() { }                     //析构函数为空
	void EdgeTransform(int start, int end, int distance);//将三元组转化为邻接矩阵 
	void Print();                       //将每个变量输出 
	int Dijkstra(int start, int end); //计算最短路径 
	int addcity(string city);//添加城市
	int deletecity(int city); //删除城市
	void writeroute(dat*& edge, int& edgenum);//route文件读写 
	void DepthSearch(int v, int s[]);//深度优先搜索参考殷人昆版数据结构P364
	//void BreadthSearch(int v, int s[]);//广度优先搜索 
private:
	T  vertex[MaxSize];                    //存放图中顶点/城市的数组
	int data[MaxSize][MaxSize];             //存放图中边的数组/城市间距离
	int nodeNum, edgeNum;                  //图的顶点数和边数
	//void Prim(dat& arr);
};
template <class Type>
class Loading		//选择装载
{
public:
	void Backtrack(int i);  //回溯算法求装载货物的最优解 
	int n, //货物个数 
		* x, //当前解
		* bestx; //当前最优解
	Type* w, //货物重量数组
		carrying, //第一批载重量
		carryweight, //当前载重量
		bestw, //当前最优载重量
		remain; //剩余的重量
};