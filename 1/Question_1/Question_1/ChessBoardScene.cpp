#include "ChessBoardScene.h"
#include <QGraphicsRectItem>
//��ʼ������
ChessBoardScene::ChessBoardScene(QObject* parent) : QGraphicsScene(parent), rows(0), cols(0)
{
    initializeColors();
}
//Ϊ��ͬ�ַ��趨��ͬ��ɫ
void ChessBoardScene::initializeColors()
{
    colorMap.insert("W", QBrush(Qt::white));
    colorMap.insert("G", QBrush(Qt::green));
    colorMap.insert("R", QBrush(Qt::red));
    colorMap.insert("B", QBrush(Qt::blue));
}
//���ó�������
void ChessBoardScene::setBoardData(const QStringList& data, int r, int c)
{
    boardData = data;
    rows = r;
    cols = c;
    items.resize(rows);
    for (auto& row : items) {
        row.resize(cols, nullptr);
    }
    clear(); // ��������е�������
    drawBoard(data, rows, cols);
}
//�ݹ������Ⱦ
void ChessBoardScene::drawBoard(const QStringList& data, int rows, int cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QGraphicsRectItem* item = addRect(j * 35, i * 35, 35, 35, QPen(), colorMap[data[i][j]]);
            item->setToolTip(data[i].mid(j, 1)); // ������ʾ����ʾ��ɫ����
            items[i][j] = item; // �洢QGraphicsRectItem����
        }
    }
}

/*
* ��ʾԭ��
*/
//void ChessBoardScene::highlightArea(const QPoint& start, const std::vector<std::vector<bool>>& visited, int maxArea)
//{
//    QBrush highlightBrush(Qt::yellow); // ���ø�����ɫ
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if (visited[i][j]) {
//                // ������ʾ�������
//                items[i][j]->setBrush(highlightBrush);
//            }
//        }
//    }
//}

/*
* ��ԭ��ֱ�����Ϊ��ɫ
*/
void ChessBoardScene::highlightArea(const QPoint& start, const std::vector<std::vector<bool>>& visited, int maxArea)
{
    QBrush highlightBrush(Qt::yellow); // ������ɫ
    QBrush blackBrush(Qt::black);     // ��ɫˢ�ӣ�����������������

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (visited[i][j]) {
                // �����������
                items[i][j]->setBrush(highlightBrush);
            }
            else {
                // ����δ��������Ϊ��ɫ
                items[i][j]->setBrush(blackBrush);
            }
        }
    }
}


//��������
void ChessBoardScene::highlightCell(int x, int y, const QBrush& brush)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols && items[x][y]) {
        items[x][y]->setBrush(brush);
    }
}