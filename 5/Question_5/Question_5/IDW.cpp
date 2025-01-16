#include "IDW.h"

IDW::IDW(const QVector<QPointF>& points, const QVector<double>& attributes, int m)
    : points_(points), attributes_(attributes), m_(m) {}

double IDW::distance(const QPointF& p1, const QPointF& p2) {
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2));
}

double IDW::interpolate(const QPointF& point) {
    QVector<std::pair<double, double>> distances; // 存储距离和属性值的配对

    // 计算所有已知点与目标点之间的距离，并与属性值一起存入distances
    for (int i = 0; i < points_.size(); ++i) {
        double dist = distance(point, points_[i]);
        if (dist != 0) { // 排除与目标点重合的情况
            distances.append({ dist, attributes_[i] });
        }
    }

    // 按照距离从小到大排序
    std::sort(distances.begin(), distances.end(), [](const std::pair<double, double>& a, const std::pair<double, double>& b) {
        return a.first < b.first;
        });

    // 选择m个最近的点
    double numerator = 0.0;
    double denominator = 0.0;
    for (int i = 0; i < m_; ++i) {
        double dist = distances[i].first;
        double attr = distances[i].second;
        if (dist > 0) {
            double weight = 1.0 / std::pow(dist, 2); // 逆距离的平方作为权重
            numerator += weight * attr;
            denominator += weight;
        }
    }

    // 计算加权平均值并返回
    return numerator / denominator;
}

