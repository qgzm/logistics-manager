#include"city.h"
template <class T>
Map<T>::Map(T a[], int n)
{
	nodeNum = n;                 //������       
	edgeNum = 0;				//�ߵ���Ŀ
	for (int i = 0; i < nodeNum; i++)
		vertex[i] = a[i];     //�������� 
	for (int i = 0; i < MaxSize; i++)    //��ʼ���ڽӾ���,�ڽӾ�������α�
		for (int j = 0; j < MaxSize; j++)
			if (i == j)
				data[i][j] = 0;
			else
				data[i][j] = 0x3f3f3f3f;			//�������0x3f3f3f3f,����С��0xc0c0c0c0
}
//������ת������Ӿ���
template <class T>
void Map<T>::EdgeTransform(int start, int end, int distance)
{
	if (start > MaxSize || end > MaxSize) throw "�������";   //������벻��ȷ�׳��쳣	
	data[start - 1][end - 1] = distance;
	data[end - 1][start - 1] = distance;
	edgeNum++;
}

//���ã���ÿ��������� 
template <class T>
void Map<T>::Print()
{
	cout << "�������ͱ���Ϊ��" << nodeNum << "," << edgeNum << endl;
	cout << "��������Ϊ��" << endl;
	for (int i = 0; i < nodeNum; i++)
	{
		cout << vertex[i] << endl;
	}
	cout << "�ڽӾ���Ϊ��" << endl;

	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			cout << data[i][j] << "    ";

		}
		cout << endl;
	}
}

//���ã�����ͼ�����·��
// �Ͻ�˹�����㷨:��һ�����·�����������Ѿ����������·��������һ��
//start ���      end   �յ� 
template <class T>
int Map<T>::Dijkstra(int start, int end)
{
	//���� 
	if (start > nodeNum || end > nodeNum || start < 0 || end < 0) throw "������Χ";
	int dist[MaxSize];                                   //��������,��ǰ���Ȩֵ ��ϵͳ������˼·������
	int path[MaxSize] = { 0 };                                   //���·��,�������·�����
	int mark[MaxSize];                                      //������ 1Ϊ�Ѿ�ʹ�� 0Ϊδʹ�� 
	int max = 0x3f3f3f3f;			//�൱��ԭ�㷨�е������
	int i, j, u, wmax;		//wmax��ǰ���

	//ʵ�� 
	for (i = 0; i < nodeNum; i++)
	{
		dist[i] = data[start][i];            //��dist��ʼ����ȡstart��õ��Ȩֵ��     
		if (i != start && dist[i] < max)         //��path��ʼ��������ͨȡ-1��                    
			path[i] = start;
		else
			path[i] = -1;
		mark[i] = 0;                       //��ÿ������Ϊδʹ��                   
	}
	mark[start] = 1; dist[start] = 0;       //�ų�start��                              
	for (u = 0; u < nodeNum - 1; u++)    //ѭ��nodeNum-1��ֱ�����е㱻�ų�����ʹ�ã�                              
	{
		wmax = max;
		j = start;
		for (i = 0; i < nodeNum; i++)            //ȡstart����Ȩֵ��͵��ڽӵ�                
		{
			if (!mark[i] && dist[i] < wmax)
			{
				j = i;
				wmax = dist[i];
			}
		}
		mark[j] = 1;								//�����ڽӵ���Ϊ��ʹ�� 
		for (i = 0; i < nodeNum; i++)            //��������start����ͨ�ĵ�����������ý������                
		{
			if (!mark[i] && dist[j] + data[j][i] < dist[i])
			{
				dist[i] = dist[j] + data[j][i]; path[i] = j;   //���ͨ·Ϊj����start����ͨ�ĵ��ʼ����ȨֵΪdist��j��+data��j����i����       
			}
		}
	}
	string line = "";                            //��ʼ���ַ���,������ž����ĳ���
	int p = end;
	while (p > -1)		//����·���Դ�ӡ
	{
		string spot = vertex[p];
		spot += line;
		line = " " + spot;
		p = path[p];
	}
	cout << endl << endl << vertex[start] << " �� " << vertex[end] << endl;
	cout << "���·��Ϊ��" << dist[end] <<"����"<< endl;
	cout << "�������У�" << line << endl << endl;
	return dist[end];
}
//���ã���city�ļ���ӳ���
template <class T>
int Map<T>::addcity(string city)
{
	ifstream infile;
	//�� (�ж��Ƿ����ظ��ĳ���)
	infile.open("city.txt", ios::in);
	if (!infile)
	{
		cout << "�ļ��޷��򿪣������ļ�����" << endl;
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
	//д 
	ofstream outfile;
	outfile.open("city.txt", ios::out);
	outfile.seekp(0, ios::beg);
	if (!outfile)
	{
		cout << "�ļ��޷��򿪣������ļ�����" << endl;
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

//���ã���city�ļ�ɾ������
//һ��city һ�� 
template <class T>
int Map<T>::deletecity(int city)
{
	if (city > nodeNum || city <= 0) throw "������Χ";
	//�������޸�   ���ļ��޸� 
	ofstream outfile;
	outfile.open("city.txt", ios::out);
	outfile.seekp(0, ios::beg);
	if (!outfile)
	{
		cout << "�ļ��޷��򿪣������ļ�����" << endl;
		return 0;
	}
	//������ 
	for (int i = city - 1; i < nodeNum; i++)
	{
		vertex[i] = vertex[i + 1];
	}
	nodeNum--;
	//д�ļ� 
	outfile << nodeNum << endl;
	for (int i = 0; i < nodeNum - 1; i++)
	{
		outfile << vertex[i] << endl;
	}
	outfile << vertex[nodeNum - 1];
	outfile.close();
	return 1;
}

//���ã���route�ļ�д����� 
//edge�ߵ���Ԫ��,�ǽṹ��
//edgenum �ߵĸ��� 
template <class T>
void Map<T>::writeroute(dat*& edge, int& edgenum)//���·��   �ļ�д��  ��д��   mainд�� 
{
	ofstream ofs;
	ofs.open("route.txt", ios::out);
	if (!ofs)
	{
		cout << "�ļ��޷��򿪣������ļ�����" << endl;
		return;
	}
	ofs << edgenum ;
	for (int i = 0; i < edgenum - 1; i++)
	{			//endlĪ����������,ֻ��ʹ��\n����
		ofs << edge[i].start << " " << edge[i].end << " " << edge[i].distance<<"\n";
	}
	ofs << edge[edgenum - 1].start << " " << edge[edgenum - 1].end << " " << edge[edgenum - 1].distance<<"\n";
	ofs.close();
}

//������ȱ����㷨(�ݹ�˼��)
//v ���
//mark ������� 
template <class T>
void Map<T>::DepthSearch(int v, int s[])
{
	cout << vertex[v] << "  ";
	s[v] = 1;//����Ѷ�ȡ 
	for (int j = 0; j < nodeNum; j++)
	{
		if (data[v][j] < 0x3f3f3f3f && s[j] == 0)DepthSearch(j, s);
	}
}

// Loading��ķ���
//���ã������㷨����ѽ�
// i�ݹ�Ĳ��� 
template <class T>
void Loading <T>::Backtrack(int i)// ������i����
{
	if (i > n)// ����Ҷ���
	{
		if (carryweight > bestw)
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];//�������Ž�
				bestw = carryweight;
			}
		}
		return;
	}
	remain -= w[i];
	if (carryweight + w[i] <= carrying) // ����������
	{
		x[i] = 1;
		carryweight += w[i];
		Backtrack(i + 1);
		carryweight -= w[i];
	}
	if (carryweight + remain > bestw)
	{
		x[i] = 0; // ����������
		Backtrack(i + 1);
	}
	remain += w[i];
}