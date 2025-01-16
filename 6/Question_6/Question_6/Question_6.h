#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Question_6.h"
#include "BuildTIN.h"
#include <QPainter>
#include <ctime>


class Question_6 : public QMainWindow
{
    Q_OBJECT

public:
    Question_6(QWidget *parent = nullptr);
    ~Question_6();

    virtual void paintEvent(QPaintEvent*);//��ͼ�¼�
public slots:
    void GetPoint();//���ص�
    void srandPoint();//���ɵ�
    void GetTin();//��ȡTIN
    void GetTrangleByPoint();//���ݵ�Ų�ѯ������
    void CleanTrangle();//ɾ����ѯ

private:
    Ui::Question_6Class ui;
    int PointNum = 0;//����
    int TrangleNum = 0;//����������
    vector<int> trangleList;//ѡ������������
    vector<int> pointlist;//ѡ�������εĵ㼯
    BuildTIN* buildtin = nullptr;
};
