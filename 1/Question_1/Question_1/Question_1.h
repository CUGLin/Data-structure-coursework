#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Question_1.h"
#include "ChessBoardScene.h"


class Question_1 : public QMainWindow
{
    Q_OBJECT

public:
    Question_1(QWidget *parent = nullptr);
    ~Question_1();

private:
    Ui::Question_1Class ui;
    ChessBoardScene* scene;  //��ʼ��GraphicsView����
    void loadBoardFromFile(const QString& fileName);
    void findMaxArea(); // �����ҵ������������
    void highlightMaxArea(); // ���ڸ�����ʾ�����������

//�����ź�
private slots:
    void on_loadButton_clicked(); //��������
    void on_selectButton_clicked(); // ��Ӧѡ���ļ���ť���
    void on_showButton_clicked(); // ��Ӧ��ʾ�ļ���ť���
    int dfs(const QStringList& boardData, std::vector<std::vector<bool>>& visited, int x, int y, const QString& color);
};
