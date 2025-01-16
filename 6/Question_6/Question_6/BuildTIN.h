#pragma once
#include<QPoint>
#include<vector>
#include<string>
#include<QFile>
#include<ctime>
using namespace std;

#define INF 1e9;

//������������
class BuildTIN
{
public:
	BuildTIN(int num);//���캯���������ָ����Ŀ��
	BuildTIN(QString fileName);//���캯����ȡcsv�ļ�
	~BuildTIN();//��������
	void CreateTin();//����TIN��
	int GetPointNum();//��ȡ����
	int GetTrangleNum();//��ȡ����������
	void GetTranglePoint(int i, QPointF& p1, QPointF& p2, QPointF& p3);//��ȡ��i�������ε���������
	void GetTranglePoint(int i, int& p1, int& p2, int& p3);//��ȡ��i�������ε���������
	vector<int> GetTrangleByPoint(int point);//��ȡ��Ŷ�Ӧ�������ε�������
	QPointF GetPoint(int i);//��ȡ��
private:
	void MinDistence();//��ȡ��С���������
	void FindPoint3();//Ѱ�ҵ�����
	bool IsRepeat(int p1, int p2, int length);//�ж�p1p2�Ƿ����������ι���
	bool IsConCurrent(int point1, int point2, int point3, int p);//�ж�p1p2p3��p1p2p4�Ƿ���ͬһ�࣬ȷ����������û��������
	int maxAngle(vector<int>& reserve, int point1, int point2);//�ҳ�����Žǵĺ�ѡ��
	double GetAngle(int p1, int p2, int p3);//��ȡp1p3p2���Ž�
private:
	int point1, point2, point3;
	vector<QPointF> PointList;//�㼯
	vector<int> t1;//�����ε�һ�����������
	vector<int> t2;//�����εڶ������������
	vector<int> t3;//�����ε��������������

};


