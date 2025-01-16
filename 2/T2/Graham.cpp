#include "Graham.h"

using namespace std;

Graham::Graham() {}

double Graham::distanceSquared(const QPointF& a, const QPointF& b) {
    return (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y());
}

double Graham::crossProduct(const QPointF& O, const QPointF& A, const QPointF& B) {
    return (A.x() - O.x()) * (B.y() - O.y()) - (A.y() - O.y()) * (B.x() - O.x());
}

bool Graham::compareY(const QPointF& a, const QPointF& b) {
    return (a.y() > b.y()) || (a.y() == b.y() && a.x() < b.x());
}

bool Graham::comparePolar(const QPointF& a, const QPointF& b) {
    double cp = crossProduct(basePoint, a, b);
    if (cp == 0) { // 共线时按距离排序
        return distanceSquared(basePoint, a) < distanceSquared(basePoint, b);
    }
    return cp > 0; // 极角从小到大排序
}

void Graham::showHullIndices(const vector<int>& indices) {
    QString indicesStr;
    for (int index : indices) {
        indicesStr += QString::number(index+1) + " ";
    }
    QMessageBox::information(nullptr, "Convex Hull Indices", "Indices of Convex Hull Points: \n" + indicesStr);
}

vector<QPointF> Graham::computeConvexHull(vector<QPointF>& points) {
    int n = points.size();
    if (n <= 2) return points;

    // 第一步：找到基准点
    basePoint = *min_element(points.begin(), points.end(), compareY);

    // 第二步：按极角排序
    sort(points.begin(), points.end(), [this](const QPointF& a, const QPointF& b) {
        return comparePolar(a, b);
        });

    // 第三步：使用栈计算凸包
    vector<QPointF> hull;
    vector<int> hullIndices; // 保存凸包点的索引
    for (size_t i = 0; i < points.size(); ++i) {
        const auto& point = points[i];
        while (hull.size() >= 2 &&
            crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], point) <= 0) {
            hull.pop_back(); // 移除不合法的点
            hullIndices.pop_back();
        }
        hull.push_back(point); // 添加当前点到凸包
        hullIndices.push_back(static_cast<int>(i));
    }

    // 显示凸包点的序号
    showHullIndices(hullIndices);

    return hull;
}
