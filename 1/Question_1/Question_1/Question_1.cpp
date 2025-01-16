#include "Question_1.h"
#include "QFileDialog.h"
#include "QTextStream.h"
#include "QMessageBox.h"
#include <iostream>
#include <vector>
#include <QCharRef>
Question_1::Question_1(QWidget *parent)
    : QMainWindow(parent), ui(), scene(new ChessBoardScene(this))
{
    ui.setupUi(this);
    ui.graphicsView->setScene(scene);

    connect(ui.LoadFile, &QPushButton::clicked, this, &Question_1::on_loadButton_clicked); // 连接信号和槽_加载数据
    connect(ui.SelectFile, &QPushButton::clicked, this, &Question_1::on_selectButton_clicked); // 连接信号和槽_显示数据
    connect(ui.ShowFile, &QPushButton::clicked, this, &Question_1::on_showButton_clicked); // 连接信号和槽_显示数据
}

Question_1::~Question_1()
{
    delete scene;  //及时清理指针释放环境
}

void Question_1::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)")); // 弹出文件选择窗口
    if (!fileName.isEmpty()) {
        loadBoardFromFile(fileName); // 加载文件
        ui.FileLine->setText(fileName); // 显示文件路径
    }
}

void Question_1::loadBoardFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QStringList boardData;

    // 读取棋盘尺寸
    QString line = in.readLine();
    QStringList sizeInfo = line.split(' ', QString::SkipEmptyParts);
    if (sizeInfo.size() != 2)
        return; // 尺寸信息不完整

    int rows = sizeInfo[0].toInt();
    int cols = sizeInfo[1].toInt();

    // 读取棋盘数据
    for (int i = 0; i < rows; ++i) {
        line = in.readLine();
        if (line.length() != cols) // 确保每行长度与列数匹配
            return;
        boardData.append(line);
    }
    file.close();

    scene->setBoardData(boardData, rows, cols);
}

void Question_1::on_selectButton_clicked()
{
    findMaxArea(); // 找到最大连续区域并更新TextFile
}

void Question_1::on_showButton_clicked()
{
    highlightMaxArea(); // 高亮显示最大连续区域
}

void Question_1::findMaxArea()
{
    QStringList boardData = scene->getBoardData(); // 从scene中获取棋盘数据
    int rows = scene->getRows();
    int cols = scene->getCols();
    if (boardData.isEmpty() || rows <= 0 || cols <= 0) {
        QMessageBox::warning(this, tr("Warning"), tr("Please load the board data first."));
        return;
    }

    int maxArea = 0;
    QChar maxColor; // 记录最大区域的颜色
    QPoint maxAreaPosition(-1, -1);

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false)); // 创建二维visited数组

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited[i][j]) {
                QChar color = boardData[i].at(j); // 获取颜色字符
                int area = dfs(boardData, visited, i, j, color);
                if (area > maxArea) {
                    maxArea = area;
                    maxColor = color; // 更新最大区域的颜色
                    maxAreaPosition = QPoint(i, j);
                }
            }
        }
    }

    // 显示最大连续区域的面积和颜色
    ui.TextFile->setText(tr("Max Area: %1\nColor: %2").arg(maxArea).arg(maxColor));
}


void Question_1::highlightMaxArea()
{   
    QStringList boardData = scene->getBoardData();
    if (boardData.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please load the board data first."));
        return;
    }

    int rows = scene->getRows();
    int cols = scene->getCols();
    int maxArea = 0;
    QPoint maxAreaPosition(-1, -1);

    // 全局 visited 数组，用于存储最大区域
    std::vector<std::vector<bool>> globalVisited(rows, std::vector<bool>(cols, false));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!globalVisited[i][j]) {
                // 局部 visited 数组，仅用于当前 DFS
                std::vector<std::vector<bool>> localVisited(rows, std::vector<bool>(cols, false));
                QChar color = boardData[i].at(j); // 获取当前格子的颜色
                int area = dfs(boardData, localVisited, i, j, color);
                if (area > maxArea) {
                    maxArea = area;
                    maxAreaPosition = QPoint(i, j);

                    // 更新全局 visited 数组为当前最大区域
                    globalVisited = localVisited;
                }
            }
        }
    }

    // 将最大区域高亮显示
    scene->highlightArea(maxAreaPosition, globalVisited, maxArea);
}

int Question_1::dfs(const QStringList& boardData, std::vector<std::vector<bool>>& visited, int x, int y, const QString& color)
{
    if (x < 0 || x >= boardData.size() || y < 0 || y >= boardData[x].size() || visited[x][y] || boardData[x].at(y) != color) {
        return 0;
    }

    visited[x][y] = true; // 标记当前格子为已访问
    int area = 1; // 当前格子作为连续区域的一部分

    // 递归地检查四个方向的相邻格子
    area += dfs(boardData, visited, x + 1, y, color); // 下
    area += dfs(boardData, visited, x - 1, y, color); // 上
    area += dfs(boardData, visited, x, y + 1, color); // 右
    area += dfs(boardData, visited, x, y - 1, color); // 左

    return area;
}

