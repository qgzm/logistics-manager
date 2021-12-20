#include"city.h"
template <class T>
Map<T>::Map(T a[], int n)
{
	nodeNum = n;                 //顶点数       
	edgeNum = 0;				//边的数目
	for (int i = 0; i < nodeNum; i++)
		vertex[i] = a[i];     //顶点名称 
	for (int i = 0; i < MaxSize; i++)    //初始化邻接矩阵,邻接矩阵定义见课本
		for (int j = 0; j < MaxSize; j++)
			if (i == j)
				data[i][j] = 0;
			else
				data[i][j] = 0x3f3f3f3f;			//无穷大是0x3f3f3f3f,无穷小是0xc0c0c0c0
}
//将数组转换成领接矩阵
template <class T>
void Map<T>::EdgeTransform(int start, int end, int distance)
{
	if (start > MaxSize || end > MaxSize) throw "顶点错误";   //如果输入不正确抛出异常	
	data[start - 1][end - 1] = distance;
	data[end - 1][start - 1] = distance;
	edgeNum++;
}

//作用：将每个变量输出 
template <class T>
void Map<T>::Print()
{
	cout << "顶点数和边数为：" << nodeNum << "," << edgeNum << endl;
	cout << "顶点名称为：" << endl;
	for (int i = 0; i < nodeNum; i++)
	{
		cout << vertex[i] << endl;
	}
	cout << "邻接矩阵为：" << endl;

	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			cout << data[i][j] << "    ";

		}
		cout << endl;
	}
}

//作用：计算图的最短路径
// 迪杰斯特拉算法:下一条最短路径总是在由已经产生的最短路径再扩充一条
//start 起点      end   终点 
template <class T>
int Map<T>::Dijkstra(int start, int end)
{
	//定义 
	if (start > nodeNum || end > nodeNum || start < 0 || end < 0) throw "超出范围";
	int dist[MaxSize];                                   //辅助数组,当前最低权值 该系统中是意思路径长度
	int path[MaxSize] = { 0 };                                   //最短路径,用来存放路径结点
	int mark[MaxSize];                                      //顶点标记 1为已经使用 0为未使用 
	int max = 0x3f3f3f3f;			//相当于原算法中的无穷大
	int i, j, u, wmax;		//wmax当前最大

	//实现 
	for (i = 0; i < nodeNum; i++)
	{
		dist[i] = data[start][i];            //将dist初始化（取start与该点的权值）     
		if (i != start && dist[i] < max)         //将path初始化（不连通取-1）                    
			path[i] = start;
		else
			path[i] = -1;
		mark[i] = 0;                       //将每个点标记为未使用                   
	}
	mark[start] = 1; dist[start] = 0;       //排除start点                              
	for (u = 0; u < nodeNum - 1; u++)    //循环nodeNum-1次直到所有点被排除（已使用）                              
	{
		wmax = max;
		j = start;
		for (i = 0; i < nodeNum; i++)            //取start点中权值最低的邻接点                
		{
			if (!mark[i] && dist[i] < wmax)
			{
				j = i;
				wmax = dist[i];
			}
		}
		mark[j] = 1;								//将该邻接点标记为已使用 
		for (i = 0; i < nodeNum; i++)            //将其他与start不联通的点用其他点做媒介连上                
		{
			if (!mark[i] && dist[j] + data[j][i] < dist[i])
			{
				dist[i] = dist[j] + data[j][i]; path[i] = j;   //最短通路为j，与start不联通的点初始化（权值为dist【j】+data【j】【i】）       
			}
		}
	}
	string line = "";                            //初始化字符串,用来存放经过的城市
	int p = end;
	while (p > -1)		//遍历路径以打印
	{
		string spot = vertex[p];
		spot += line;
		line = " " + spot;
		p = path[p];
	}
	cout << endl << endl << vertex[start] << " 到 " << vertex[end] << endl;
	cout << "最短路径为：" << dist[end] <<"公里"<< endl;
	cout << "经过城市：" << line << endl << endl;
	return dist[end];
}
//作用：在city文件添加城市
template <class T>
int Map<T>::addcity(string city)
{
	ifstream infile;
	//读 (判断是否有重复的城市)
	infile.open("city.txt", ios::in);
	if (!infile)
	{
		cout << "文件无法打开，请检查文件再试" << endl;
		return 0;
	}
	int filelong;
	infile >> filelong;
	T  vertex2[MaxSize];
	for (int i = 0; i < filelong; i++)
	{
		infile >> vertex2[i];
		if (vertex2[i] == city)  return 2;
	}
	infile.close();
	//写 
	ofstream outfile;
	outfile.open("city.txt", ios::out);
	outfile.seekp(0, ios::beg);
	if (!outfile)
	{
		cout << "文件无法打开，请检查文件再试" << endl;
		return 0;
	}
	vertex[nodeNum] = city;
	nodeNum++;
	outfile << nodeNum << endl;
	for (int i = 1; i < nodeNum; i++)
	{
		outfile << vertex[i - 1] << endl;
	}
	outfile << vertex[nodeNum - 1];
	outfile.close();
	return 1;
}

//作用：在city文件删除城市
//一个city 一行 
template <class T>
int Map<T>::deletecity(int city)
{
	if (city > nodeNum || city <= 0) throw "超出范围";
	//先数组修改   再文件修改 
	ofstream outfile;
	outfile.open("city.txt", ios::out);
	outfile.seekp(0, ios::beg);
	if (!outfile)
	{
		cout << "文件无法打开，请检查文件再试" << endl;
		return 0;
	}
	//改数组 
	for (int i = city - 1; i < nodeNum; i++)
	{
		vertex[i] = vertex[i + 1];
	}
	nodeNum--;
	//写文件 
	outfile << nodeNum << endl;
	for (int i = 0; i < nodeNum - 1; i++)
	{
		outfile << vertex[i] << endl;
	}
	outfile << vertex[nodeNum - 1];
	outfile.close();
	return 1;
}

//作用：在route文件写入操作 
//edge边的三元组,是结构体
//edgenum 边的个数 
template <class T>
void Map<T>::writeroute(dat*& edge, int& edgenum)//添加路线   文件写入  类写入   main写入 
{
	ofstream ofs;
	ofs.open("route.txt", ios::out);
	if (!ofs)
	{
		cout << "文件无法打开，请检查文件再试" << endl;
		return;
	}
	ofs << edgenum ;
	for (int i = 0; i < edgenum - 1; i++)
	{			//endl莫名出现问题,只能使用\n代替
		ofs << edge[i].start << " " << edge[i].end << " " << edge[i].distance<<"\n";
	}
	ofs << edge[edgenum - 1].start << " " << edge[edgenum - 1].end << " " << edge[edgenum - 1].distance<<"\n";
	ofs.close();
}

//深度优先遍历算法(递归思想)
//v 起点
//mark 标记数组 
template <class T>
void Map<T>::DepthSearch(int v, int s[])
{
	cout << vertex[v] << "  ";
	s[v] = 1;//标记已读取 
	for (int j = 0; j < nodeNum; j++)
	{
		if (data[v][j] < 0x3f3f3f3f && s[j] == 0)DepthSearch(j, s);
	}
}

// Loading类的方法
//作用：回溯算法求最佳解
// i递归的层数 
template <class T>
void Loading <T>::Backtrack(int i)// 搜索第i层结点
{
	if (i > n)// 到达叶结点
	{
		if (carryweight > bestw)
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];//更新最优解
				bestw = carryweight;
			}
		}
		return;
	}
	remain -= w[i];
	if (carryweight + w[i] <= carrying) // 搜索左子树
	{
		x[i] = 1;
		carryweight += w[i];
		Backtrack(i + 1);
		carryweight -= w[i];
	}
	if (carryweight + remain > bestw)
	{
		x[i] = 0; // 搜索右子树
		Backtrack(i + 1);
	}
	remain += w[i];
}