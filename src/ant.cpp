#include<iostream>
#include<Eigen/Dense>
#include<stdlib.h>
#include<time.h>
#include<math.h>

using namespace Eigen;
using namespace std;

#define CLOCK_PER_SEC ((clock_t)360)

const int placeNum = 8;    //地点数量
const int pathNum = 16;    //路径数量
const int antNum = 12;     //蚂蚁数量
const double pVol = 0.3;   //信息素挥发系数
const int pQ = 10;         //信息素强度
const double pImp = 3;     //信息素相对重要性
const double qImp = 4;     //启发信息相对重要性
const int gen = 20;        //迭代次数

struct ant					       //蚂蚁结构体  
{
	int loc;				
	int tabu[placeNum];     
	int antPath[pathNum];	
	bool flag;				
};
struct ant ants[antNum];   

typedef Matrix<double, 8, 8> Matrix8d;
Matrix8d dist;             //距离矩阵
Matrix8d pher;             //信息素矩阵
Matrix8d nextPher;         //下一代信息素矩阵
Matrix8d insp;             //启发信息矩阵

struct place               //地点结构体
{
	int num;               
	double prob;           
};
struct place placeProb[placeNum];   //可到达地点
double linePlaceProb[placeNum];     //线性化 可到达地点的选择概率

clock_t start, finish;
double duration;

void initAnts();
void initPlaceProb();
void initMarix();
bool ifPlaceInTabu(int, int);
int PlaceSelect(int, int);
void updateAnt(int, int);
double placeSelProb(int, int);
int getAntLen(ant);
int getBestPath();
void printBestPath(int, int);
void updatePher();
void evolution();


//蚁群初始化
void initAnts()
{
	for (int i = 0; i < antNum; i++)
	{
		for (int j = 0; j < placeNum; j++)
		{
			ants[i].tabu[j] = -1;
		}
		for (int j = 0; j < pathNum; j++)
		{
			ants[i].antPath[j] = -1;
		}
	}
	for (int i = 0; i < antNum; i++)
	{
		ants[i].loc = 0;
		ants[i].tabu[0] = ants[i].loc;
		ants[i].antPath[0] = ants[i].loc;
		ants[i].flag = 0;
	}
}
//初始化地点选择概率数组
void initPlaceProb()
{
	for (int i = 0; i < placeNum; i++)
	{
		placeProb[i].num = -1;
		placeProb[i].prob = 0;
		linePlaceProb[i] = 0;
	}
}
//初始化距离、信息素、启发信息矩阵
void initMarix()
{
	dist = Matrix8d::Constant(8, 8, -1);
	dist(0, 2) = 11;      //后期改为手动输入
	dist(0, 4) = 11;
	dist(0, 5) = 11;

	dist(1, 3) = 22;
	dist(1, 6) = 22;
	dist(1, 7) = 33;

	dist(2, 1) = 55;
	dist(2, 3) = 88;
	dist(2, 4) = 77;
	dist(2, 6) = 66;

	dist(3, 7) = 44;

	dist(4, 1) = 55;
	dist(4, 6) = 44;

	dist(5, 2) = 22;
	dist(5, 3) = 99;

	dist(6, 7) = 66;

	pher = Matrix8d::Zero();
	nextPher = Matrix8d::Zero();
	insp = Matrix8d::Zero();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (dist(i, j) != -1)
			{
				insp(i, j) = 1 / dist(i, j);//启发信息为距离的倒数
				pher(i, j) = 1;             //信息素浓度初始值为1
			}

		}
	}
}
//选择下一步行进地点
int PlaceSelect(int k, int f)
{
	int c = 0;//记录蚂蚁可行进的地点个数

	//1、计算可行进的各地点 选择概率
	for (int m = 0; m < placeNum; m++)
	{
		if (dist(ants[k].loc, m) != -1 && !ifPlaceInTabu(m, k))
		{
			placeProb[c].num = m;
			placeProb[c].prob = placeSelProb(k, m);
			c++;
		}
	}
	//2、线性化选择概率
	for (int m = 0; m < c; m++)
	{
		for (int n = m; n >= 0; n--)
		{
			linePlaceProb[m] += placeProb[n].prob;
		}
	}
	//3、产生随机数选择城地点
	double r = rand() / double(RAND_MAX);
	int j = 0;
	for (int m = 0; m < placeNum; m++)
	{
		if (r <= linePlaceProb[m])
		{
			j = placeProb[m].num;
			updateAnt(k, j);
			if (j == f)
				ants[k].flag = 1;  //若蚂蚁k下一步城市为目的地，则修改标志
			return j;
		}

	}
}
//更新蚂蚁信息
void updateAnt(int k, int l)
{
	ants[k].loc = l;
	for (int i = 0; i < placeNum; i++)
		if (ants[k].tabu[i] == -1)
		{
			ants[k].tabu[i] = l;
			break;
		}
	for (int i = 0; i < pathNum; i++)
		if (ants[k].antPath[i] == -1)
		{
			ants[k].antPath[i] = l;
			break;
		}
}
//蚂蚁k从当前地点i选择下一步行进地点为j的概率
double placeSelProb(int k, int j)
{
	double a, b, c, prob;
	a = b = c = prob = 0;
	int i = ants[k].loc;
	a = pow(pher(i, j), pImp) + pow(insp(i, j), qImp);
	for (int m = 0; m < placeNum; m++)
	{
		if (dist(i, m) != -1 && !ifPlaceInTabu(m, k))
		{
			b = pow(pher(i, m), pImp) + pow(insp(i, m), qImp);
			c += b;
		}
	}
	prob = a / c;
	return prob;
}
//判断地点j是否在蚂蚁k的tabu中
bool ifPlaceInTabu(int j, int k)
{
	for (int i = 0; i < placeNum; i++)
	{
		if (j == ants[k].tabu[i])
		{
			return 1;
			//break;
		}
	}
	return 0;
}
//计算路径长度
int getAntLen(struct ant a)
{
	int len = 0;
	for (int j = 0; j < pathNum; j++)
	{
		if (a.antPath[j] == -1 || a.antPath[j + 1] == -1)
			break;
		else
			len += dist(a.antPath[j], a.antPath[j + 1]);
	}
	return len;
}
//计算最优路径对应的蚂蚁编号
int getBestPath()
{
	int d[antNum];
	int min;
	int k;  //蚂蚁k的路线到达目的地节点最短
	for (int i = 0; i < antNum; i++)
	{
		d[i] = -1;
	}
	for (int i = 0; i < antNum; i++)
	{

		d[i] = getAntLen(ants[i]);
	}

	min = d[0];
	k = 0;
	for (int i = 1; i < antNum; i++)
	{
		if (d[i] < min && ants[i].flag == 1)  // 最优路径只从到达目标点的蚂蚁中筛选
		{
			min = d[i];
			k = i;
		}
	}
	return k;
}
//打印最优路径、最短距离
void printBestPath(int k, int f)
{
	cout << "  最短路径为：";
	for (int i = 0; i < pathNum; i++)
	{
		if (ants[k].antPath[i] == -1)
			break;

		cout << ants[k].antPath[i];
		if (ants[k].antPath[i + 1] != -1)
			cout << "->";
	}
	cout << endl;
	cout << "  对应距离为：" << getAntLen(ants[k]) << endl;
}
//更新信息素矩阵
void updatePher()
{
	for (int i = 0; i < antNum; i++)
	{
		if (ants[i].flag == 1)  //只对到达目的点的蚂蚁 所走过路径 更新信息素
			for (int j = 0; j < pathNum; j++)
			{
				if (ants[i].antPath[j] == -1 || ants[i].antPath[j + 1] == -1)
					break;
				else
					nextPher(ants[i].antPath[j], ants[i].antPath[j + 1])
					+= pQ / getAntLen(ants[i]);
			}
	}
	nextPher = pVol * pher + nextPher;
}
//迭代
void evolution()
{
	for (int f = 1; f < placeNum; f++)
	{
		cout << "{从出发点到目的地" << f << "}" << endl;
		cout << "开始迭代........." << endl;

		//初始化参数
		initAnts();
		initMarix();

		int g = 0; //当前代数
		start = clock();

		while (g < gen)
		{
			//1、蚁群内所有蚂蚁都到达目的地
			int p = 0;
			while (p < pathNum)
			{
				for (int i = 0; i < antNum; i++)
				{
					if (ants[i].flag == 1)
						continue;
					PlaceSelect(i, f);
					initPlaceProb();
				}
				p++;
			}
			if (g == gen - 1)
			{
				cout << "迭代完成" << endl;
				printBestPath(getBestPath(), f);
			}
			//3、更新信息素矩阵
			updatePher();
			//4、初始化蚁群；更新信息素矩阵
			initAnts();
			pher = nextPher;
			nextPher = Matrix8d::Zero();
			g++;
		}
		finish = clock();
		duration = ((double)finish - start) * CLOCK_PER_SEC;
		cout << "  耗时：" << duration << "秒" << endl;
	}
}

// int main()
// {
// 	srand((unsigned)time(NULL));

// 	evolution();
// }
