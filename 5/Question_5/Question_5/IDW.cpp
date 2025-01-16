#include "IDW.h"

IDW::IDW(const QVector<QPointF>& points, const QVector<double>& attributes, int m)
    : points_(points), attributes_(attributes), m_(m) {}

double IDW::distance(const QPointF& p1, const QPointF& p2) {
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2));
}

double IDW::interpolate(const QPointF& point) {
    QVector<std::pair<double, double>> distances; // �洢���������ֵ�����

    // ����������֪����Ŀ���֮��ľ��룬��������ֵһ�����distances
    for (int i = 0; i < points_.size(); ++i) {
        double dist = distance(point, points_[i]);
        if (dist != 0) { // �ų���Ŀ����غϵ����
            distances.append({ dist, attributes_[i] });
        }
    }

    // ���վ����С��������
    std::sort(distances.begin(), distances.end(), [](const std::pair<double, double>& a, const std::pair<double, double>& b) {
        return a.first < b.first;
        });

    // ѡ��m������ĵ�
    double numerator = 0.0;
    double denominator = 0.0;
    for (int i = 0; i < m_; ++i) {
        double dist = distances[i].first;
        double attr = distances[i].second;
        if (dist > 0) {
            double weight = 1.0 / std::pow(dist, 2); // ������ƽ����ΪȨ��
            numerator += weight * attr;
            denominator += weight;
        }
    }

    // �����Ȩƽ��ֵ������
    return numerator / denominator;
}

