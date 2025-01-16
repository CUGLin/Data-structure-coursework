
#include "BuildTIN.h"

//���캯������ָ�������Ĳ��ظ��������
BuildTIN::BuildTIN(int num)
{
	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		int X = rand() % 942 + 10;
		int Y = rand() % 942 + 10;
		QPointF point(X, Y);
		bool flag = false;
		for (int i = 0; i < PointList.size(); i++)
		{
			if (PointList[i].x() == X && PointList[i].y() == Y)
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			continue;
		}
		PointList.push_back(point);
	}
	MinDistence();//Ѱ�Ҿ�����С������
	FindPoint3();//Ѱ�ҵ�����
}

//���캯��
BuildTIN::BuildTIN(QString fileName)
{
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	int i = 0;
	while (!file.atEnd())
	{
		QString line = file.readLine();
		if (i == 0)
		{
			i++;
			continue;
		}
		const QStringList columnStrings = line.split(QLatin1Char(','));
		QPointF point((columnStrings[2].toDouble() - 114) * 2000 - 300, (columnStrings[3].toDouble() - 30) * 2000 - 550);
		PointList.push_back(point);
		i++;
	}
	MinDistence();//Ѱ�Ҿ�����С������
	FindPoint3();//Ѱ�ҵ�����
}

//��������
BuildTIN::~BuildTIN()
{
	PointList.clear();
}

//����TIN��
void BuildTIN::CreateTin()
{
	t1.clear();
	t2.clear();
	t3.clear();

	//���������̵�����
	t1.push_back(point1);
	t2.push_back(point2);

	//Ѱ�Ҿ����һ���߾�����̵ĵ�������
	t3.push_back(point3);

	int k = 0;//��¼��չ����������
	int L = 1;//��¼������������
	int p1, p2, p3;//��¼�����ε���������
	vector<int> reserve;//���ܴ��ڵ���չ��

	while (k != L)
	{
		p1 = t1[k];
		p2 = t2[k];
		p3 = t3[k];
		k++;

		//��һ����չ�ߣ�p1p2��û���ظ�ʹ��
		if (IsRepeat(p1, p2, L))
		{
			reserve.clear();
			for (int i = 0; i < PointList.size(); i++)
			{
				if (i != p1 && i != p2 && i != p3 && IsConCurrent(p1, p2, p3, i))
				{
					reserve.push_back(i);
				}
			}
			if (reserve.size() > 0)
			{
				int max = maxAngle(reserve, p1, p2);
				t1.push_back(p1);
				t2.push_back(p2);
				t3.push_back(max);
				L++;
			}
		}

		//�ڶ�����չ��p1p3û���ظ�����
		if (IsRepeat(p1, p3, L))
		{
			reserve.clear();
			for (int i = 0; i < PointList.size(); i++)
			{
				if (i != p1 && i != p3 && i != p2 && IsConCurrent(p1, p3, p2, i))
				{
					reserve.push_back(i);
				}
			}
			if (reserve.size() > 0)
			{
				int max = maxAngle(reserve, p1, p3);
				t1.push_back(p1);
				t2.push_back(p3);
				t3.push_back(max);
				L++;
			}
		}

		//��������չ��p2p3û���ظ�����
		if (IsRepeat(p2, p3, L))
		{
			reserve.clear();
			for (int i = 0; i < PointList.size(); i++)
			{
				if (i != p2 && i != p3 && i != p1 && IsConCurrent(p2, p3, p1, i))
				{
					reserve.push_back(i);
				}
			}
			if (reserve.size() > 0)
			{
				int max = maxAngle(reserve, p2, p3);
				t1.push_back(p2);
				t2.push_back(p3);
				t3.push_back(max);
				L++;
			}
		}
	}
}

//��ȡ��С���������
void BuildTIN::MinDistence()
{
	int min1 = 0, min2 = 0;//��С���������
	int min = INF;//��С����
	for (int i = 0; i < PointList.size() - 1; i++)
	{
		for (int j = i + 1; j < PointList.size(); j++)
		{
			double length = pow((PointList[i].x() - PointList[j].x()) * (PointList[i].x() - PointList[j].x()) + (PointList[i].y() - PointList[j].y()) * (PointList[i].y() - PointList[j].y()), 0.5);
			if (length < min)
			{
				min = length;
				min1 = i;
				min2 = j;
			}
		}
	}
	this->point1 = min1;
	this->point2 = min2;
}

//Ѱ�ҵ�����
void BuildTIN::FindPoint3()
{
	double meanX = double(PointList[point1].x() + PointList[point2].x()) / 2;
	double meanY = double(PointList[point1].y() + PointList[point2].y()) / 2;
	double min = INF;
	int min3 = 0;
	for (int i = 0; i < PointList.size(); i++)
	{
		if (i != point1 && i != point2)
		{
			double length = pow((PointList[i].x() - meanX) * (PointList[i].x() - meanX) + (PointList[i].y() - meanY) * (PointList[i].y() - meanY), 0.5);
			if (length < min)
			{
				min = length;
				min3 = i;
			}
		}
	}
	point3 = min3;
}

//�ж�p1p2�Ƿ����������ι���
bool BuildTIN::IsRepeat(int p1, int p2, int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		if (p1 == t1[i] && p2 == t2[i] || p1 == t2[i] && p2 == t1[i] ||
			p1 == t1[i] && p2 == t3[i] || p1 == t3[i] && p2 == t1[i] ||
			p1 == t2[i] && p2 == t3[i] || p1 == t3[i] && p2 == t2[i])
		{
			sum++;
		}
		if (sum >= 2)
		{
			return false;
		}
	}
	return true;
}

//�ж�p1p2p3��p1p2p4�Ƿ���ͬһ�࣬ȷ����������û��������
bool BuildTIN::IsConCurrent(int point1, int point2, int point3, int p)
{
	double a = double(PointList[point2].y() - PointList[point1].y()) / (PointList[point2].x() - PointList[point1].x());
	double b = double(PointList[point1].x() * PointList[point2].y() - PointList[point2].x() * PointList[point1].y()) / (PointList[point2].x() - PointList[point1].x());
	double fxy1 = PointList[point3].y() - (a * PointList[point3].x() - b);
	double fxy2 = PointList[p].y() - (a * PointList[p].x() - b);
	//λ�ڶԲ�
	if (fxy1 * fxy2 <= 0)
	{
		return true;
	}
	return false;
}

//��ȡ����Ž�λ�õĵ�
int BuildTIN::maxAngle(vector<int>& reserve, int point1, int point2)
{
	int max = 0; double maxAngle = INF;
	for (int i = 0; i < reserve.size(); i++)
	{
		double angle = GetAngle(point1, point2, reserve[i]);
		if (angle < maxAngle)
		{
			maxAngle = angle;
			max = reserve[i];
		}
	}
	return max;
}

//��ȡp1p3p2���Ž�
double BuildTIN::GetAngle(int p1, int p2, int p3)
{
	double d1 = (PointList[p2].x() - PointList[p3].x()) * (PointList[p2].x() - PointList[p3].x()) + (PointList[p2].y() - PointList[p3].y()) * (PointList[p2].y() - PointList[p3].y());
	double d2 = (PointList[p1].x() - PointList[p3].x()) * (PointList[p1].x() - PointList[p3].x()) + (PointList[p1].y() - PointList[p3].y()) * (PointList[p1].y() - PointList[p3].y());
	double d3 = (PointList[p1].x() - PointList[p2].x()) * (PointList[p1].x() - PointList[p2].x()) + (PointList[p1].y() - PointList[p2].y()) * (PointList[p1].y() - PointList[p2].y());
	double angle = (d1 + d2 - d3) / (2 * pow(d1, 0.5) * pow(d2, 0.5));
	return angle;
}

//��ȡ����
int BuildTIN::GetPointNum()
{
	return PointList.size();
}

//��ȡ�����θ���
int BuildTIN::GetTrangleNum()
{
	return t1.size();
}


//��ȡ�����������ε���������
void BuildTIN::GetTranglePoint(int i, QPointF& p1, QPointF& p2, QPointF& p3)
{
	p1 = PointList[t1[i]];
	p2 = PointList[t2[i]];
	p3 = PointList[t3[i]];
}

void BuildTIN::GetTranglePoint(int i, int& p1, int& p2, int& p3)
{
	p1 = t1[i];
	p2 = t2[i];
	p3 = t3[i];
}

vector<int> BuildTIN::GetTrangleByPoint(int point)
{
	vector<int> tempList;
	for (int i = 0; i < t1.size(); i++)
	{
		if (t1[i] == point || t2[i] == point || t3[i] == point)
		{
			tempList.push_back(i);
		}
	}
	return tempList;
}

//��ȡ��
QPointF BuildTIN::GetPoint(int i)
{
	if (i >= PointList.size())
	{
		return PointList[PointList.size() - 1];
	}
	//QPoint point((PointList[i].x() * 111 - 12654) * 6, (PointList[i].y() * 111 - 3300) * 5);
	return PointList[i];
}


