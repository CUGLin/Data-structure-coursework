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
    ChessBoardScene* scene;  //初始化GraphicsView场景
    void loadBoardFromFile(const QString& fileName);
    void findMaxArea(); // 用于找到最大连续区域
    void highlightMaxArea(); // 用于高亮显示最大连续区域

//定义信号
private slots:
    void on_loadButton_clicked(); //加载数据
    void on_selectButton_clicked(); // 响应选择文件按钮点击
    void on_showButton_clicked(); // 响应显示文件按钮点击
    int dfs(const QStringList& boardData, std::vector<std::vector<bool>>& visited, int x, int y, const QString& color);
};
