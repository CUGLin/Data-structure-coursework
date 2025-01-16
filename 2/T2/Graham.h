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
	//构造函数
	Graham();

	// 计算凸包的函数
	vector<QPointF> computeConvexHull(vector<QPointF>& points);

private:
    // 基准点
    QPointF basePoint;

    // 计算两点之间的距离平方
    double distanceSquared(const QPointF& a, const QPointF& b);

    // 计算叉积，用于判断方向
    double crossProduct(const QPointF& O, const QPointF& A, const QPointF& B);

    // 找到 y 最小的点作为基准点
    static bool compareY(const QPointF& a, const QPointF& b);

    // 按极角排序的比较函数
    bool comparePolar(const QPointF& a, const QPointF& b);

    // 显示凸包点的序号
    void showHullIndices(const vector<int>& indices);
};

