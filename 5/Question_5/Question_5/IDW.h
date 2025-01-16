#ifndef IDW_H
#define IDW_H

#include <QVector>
#include <QPointF>
#include <cmath>

class IDW {
public:
    // 构造函数，传入点坐标和属性值
    IDW(const QVector<QPointF>& points, const QVector<double>& attributes, int m);

    // 进行插值计算，返回指定点的插值结果
    double interpolate(const QPointF& point);

private:
    QVector<QPointF> points_;   // 存储所有已知点的坐标
    QVector<double> attributes_; // 存储所有已知点的属性值
    int m_; // 最近邻点数

    // 计算两点之间的欧几里得距离
    double distance(const QPointF& p1, const QPointF& p2);
};

#endif // IDW_H
