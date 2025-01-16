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
    if (cp == 0) { // ����ʱ����������
        return distanceSquared(basePoint, a) < distanceSquared(basePoint, b);
    }
    return cp > 0; // ���Ǵ�С��������
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

    // ��һ�����ҵ���׼��
    basePoint = *min_element(points.begin(), points.end(), compareY);

    // �ڶ���������������
    sort(points.begin(), points.end(), [this](const QPointF& a, const QPointF& b) {
        return comparePolar(a, b);
        });

    // ��������ʹ��ջ����͹��
    vector<QPointF> hull;
    vector<int> hullIndices; // ����͹���������
    for (size_t i = 0; i < points.size(); ++i) {
        const auto& point = points[i];
        while (hull.size() >= 2 &&
            crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], point) <= 0) {
            hull.pop_back(); // �Ƴ����Ϸ��ĵ�
            hullIndices.pop_back();
        }
        hull.push_back(point); // ��ӵ�ǰ�㵽͹��
        hullIndices.push_back(static_cast<int>(i));
    }

    // ��ʾ͹��������
    showHullIndices(hullIndices);

    return hull;
}
