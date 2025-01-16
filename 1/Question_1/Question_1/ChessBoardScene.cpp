#include "ChessBoardScene.h"
#include <QGraphicsRectItem>
//初始化棋盘
ChessBoardScene::ChessBoardScene(QObject* parent) : QGraphicsScene(parent), rows(0), cols(0)
{
    initializeColors();
}
//为不同字符设定不同颜色
void ChessBoardScene::initializeColors()
{
    colorMap.insert("W", QBrush(Qt::white));
    colorMap.insert("G", QBrush(Qt::green));
    colorMap.insert("R", QBrush(Qt::red));
    colorMap.insert("B", QBrush(Qt::blue));
}
//设置场景参数
void ChessBoardScene::setBoardData(const QStringList& data, int r, int c)
{
    boardData = data;
    rows = r;
    cols = c;
    items.resize(rows);
    for (auto& row : items) {
        row.resize(cols, nullptr);
    }
    clear(); // 清除场景中的所有项
    drawBoard(data, rows, cols);
}
//递归进行渲染
void ChessBoardScene::drawBoard(const QStringList& data, int rows, int cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QGraphicsRectItem* item = addRect(j * 35, i * 35, 35, 35, QPen(), colorMap[data[i][j]]);
            item->setToolTip(data[i].mid(j, 1)); // 设置提示，显示颜色代码
            items[i][j] = item; // 存储QGraphicsRectItem对象
        }
    }
}

/*
* 显示原来
*/
//void ChessBoardScene::highlightArea(const QPoint& start, const std::vector<std::vector<bool>>& visited, int maxArea)
//{
//    QBrush highlightBrush(Qt::yellow); // 设置高亮颜色
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if (visited[i][j]) {
//                // 高亮显示最大区域
//                items[i][j]->setBrush(highlightBrush);
//            }
//        }
//    }
//}

/*
* 将原来直接填充为黑色
*/
void ChessBoardScene::highlightArea(const QPoint& start, const std::vector<std::vector<bool>>& visited, int maxArea)
{
    QBrush highlightBrush(Qt::yellow); // 高亮颜色
    QBrush blackBrush(Qt::black);     // 黑色刷子，用于隐藏其他区域

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (visited[i][j]) {
                // 高亮最大区域
                items[i][j]->setBrush(highlightBrush);
            }
            else {
                // 设置未访问区域为黑色
                items[i][j]->setBrush(blackBrush);
            }
        }
    }
}


//高亮处理
void ChessBoardScene::highlightCell(int x, int y, const QBrush& brush)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols && items[x][y]) {
        items[x][y]->setBrush(brush);
    }
}