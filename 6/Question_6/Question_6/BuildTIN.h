#pragma once
#include<QPoint>
#include<vector>
#include<string>
#include<QFile>
#include<ctime>
using namespace std;

#define INF 1e9;

//创建三角网类
class BuildTIN
{
public:
	BuildTIN(int num);//构造函数生成随机指定数目点
	BuildTIN(QString fileName);//构造函数读取csv文件
	~BuildTIN();//析构函数
	void CreateTin();//创建TIN网
	int GetPointNum();//获取点数
	int GetTrangleNum();//获取三角形数量
	void GetTranglePoint(int i, QPointF& p1, QPointF& p2, QPointF& p3);//获取第i个三角形的三个顶点
	void GetTranglePoint(int i, int& p1, int& p2, int& p3);//获取第i个三角形的三个顶点
	vector<int> GetTrangleByPoint(int point);//获取点号对应的三角形的三个点
	QPointF GetPoint(int i);//获取点
private:
	void MinDistence();//获取最小距离的两点
	void FindPoint3();//寻找第三边
	bool IsRepeat(int p1, int p2, int length);//判断p1p2是否被两个三角形公用
	bool IsConCurrent(int point1, int point2, int point3, int p);//判断p1p2p3和p1p2p4是否在同一侧，确保三角形中没有其他点
	int maxAngle(vector<int>& reserve, int point1, int point2);//找出最大张角的候选点
	double GetAngle(int p1, int p2, int p3);//获取p1p3p2的张角
private:
	int point1, point2, point3;
	vector<QPointF> PointList;//点集
	vector<int> t1;//三角形第一个顶点的数组
	vector<int> t2;//三角形第二个顶点的数组
	vector<int> t3;//三角形第三个顶点的数组

};


