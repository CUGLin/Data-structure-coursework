#include "Question_6.h"

Question_6::Question_6(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setFixedSize(1280,960);//设置固定大小


    connect(ui.GetTinBtn, &QPushButton::clicked, this, &Question_6::GetTin);//根据输入插值点
    connect(ui.SearchBtn, &QPushButton::clicked, this, &Question_6::GetTrangleByPoint);//根据输入插值点
    connect(ui.CleanBtn, &QPushButton::clicked, this, &Question_6::CleanTrangle);//根据输入插值点
    connect(ui.srandBtn, &QPushButton::clicked, this, &Question_6::srandPoint);//根据输入插值点
}

Question_6::~Question_6()
{}

//绘图事件
void Question_6::paintEvent(QPaintEvent*)
{
    //实例化画家对象
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(255, 255, 255), Qt::SolidPattern));//将笔画刷设置为白色
    painter.drawRect(10, 10, 950, 900);//调用矩形函数画背景

    if (buildtin == nullptr)
    {
        return;
    }

    //绘制线要素
    painter.setPen(QPen(QColor(156, 156, 156), 1));
    for (int i = 0; i < buildtin->GetTrangleNum(); i++)
    {
        QPointF p1, p2, p3;
        buildtin->GetTranglePoint(i, p1, p2, p3);
        painter.drawLine(p1, p2);
        painter.drawLine(p2, p3);
        painter.drawLine(p3, p1);
    }

    //绘制点要素
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    for (int i = 0; i < buildtin->GetPointNum(); i++)
    {

        painter.drawEllipse(buildtin->GetPoint(i), 1, 1);
    }

    //绘制选中点要素
    painter.setPen(QPen(QColor(255, 0, 0), 2));
    for (int i = 0; i < trangleList.size(); i++)
    {
        QPointF p1, p2, p3;
        buildtin->GetTranglePoint(trangleList[i], p1, p2, p3);
        painter.drawLine(p1, p2);
        painter.drawLine(p2, p3);
        painter.drawLine(p3, p1);
    }
    painter.setPen(QPen(QColor(0, 0, 255), 2));
    for (int i = 0; i < pointlist.size(); i++)
    {
        painter.drawText(buildtin->GetPoint(pointlist[i]), QString::number(pointlist[i]));
    }


}

//加载点
void Question_6::GetPoint()
{
    ui.textEdit->clear();
    if (buildtin != nullptr)
    {
        delete buildtin;
        trangleList.clear();
        pointlist.clear();
    }
    buildtin = new BuildTIN(QString::fromLocal8Bit("E:/VS_Project/YL/Test_Data/TIN_data.csv"));
    update();
}

//生成点
void Question_6::srandPoint()
{
    ui.textEdit->clear();
    if (buildtin != nullptr)
    {
        delete buildtin;
        trangleList.clear();
        pointlist.clear();
    }
    buildtin = new BuildTIN(ui.spinBox_2->value());
    update();
}

//获取Tin
void Question_6::GetTin()
{
    if (buildtin)
    {
        buildtin->CreateTin();
        update();
    }
}

//获取某点号对应的三角形
void Question_6::GetTrangleByPoint()
{
    if (buildtin == nullptr)
    {
        return;
    }
    trangleList.clear();
    pointlist.clear();
    ui.textEdit->clear();
    trangleList = buildtin->GetTrangleByPoint(ui.spinBox->value());
    for (int i = 0; i < trangleList.size(); i++)
    {
        int p1, p2, p3;
        buildtin->GetTranglePoint(trangleList[i], p1, p2, p3);
        ui.textEdit->append(QStringLiteral("三角形构成：") + QString::number(p1) + "-" + QString::number(p2) + "-" + QString::number(p3));
        pointlist.push_back(p1);
        pointlist.push_back(p2);
        pointlist.push_back(p3);
    }
    update();
}

//清除查询
void Question_6::CleanTrangle()
{
    trangleList.clear();
    pointlist.clear();
    ui.textEdit->clear();
    update();
}