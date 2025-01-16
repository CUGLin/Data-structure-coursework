#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include <QPointF>
#include <QMessageBox>
using namespace std;

class Graham
{
public:
	//���캯��
	Graham();

	// ����͹���ĺ���
	vector<QPointF> computeConvexHull(vector<QPointF>& points);

private:
    // ��׼��
    QPointF basePoint;

    // ��������֮��ľ���ƽ��
    double distanceSquared(const QPointF& a, const QPointF& b);

    // �������������жϷ���
    double crossProduct(const QPointF& O, const QPointF& A, const QPointF& B);

    // �ҵ� y ��С�ĵ���Ϊ��׼��
    static bool compareY(const QPointF& a, const QPointF& b);

    // ����������ıȽϺ���
    bool comparePolar(const QPointF& a, const QPointF& b);

    // ��ʾ͹��������
    void showHullIndices(const vector<int>& indices);
};

