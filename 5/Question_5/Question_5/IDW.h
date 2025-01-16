#ifndef IDW_H
#define IDW_H

#include <QVector>
#include <QPointF>
#include <cmath>

class IDW {
public:
    // ���캯������������������ֵ
    IDW(const QVector<QPointF>& points, const QVector<double>& attributes, int m);

    // ���в�ֵ���㣬����ָ����Ĳ�ֵ���
    double interpolate(const QPointF& point);

private:
    QVector<QPointF> points_;   // �洢������֪�������
    QVector<double> attributes_; // �洢������֪�������ֵ
    int m_; // ����ڵ���

    // ��������֮���ŷ����þ���
    double distance(const QPointF& p1, const QPointF& p2);
};

#endif // IDW_H
