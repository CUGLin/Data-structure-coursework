#ifndef CHESSBOARDSCENE_H
#define CHESSBOARDSCENE_H

#include <QGraphicsScene>
#include <QMap>
#include <QBrush>
#include <QStringList>
#include <QVector>
#include <vector>

class ChessBoardScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ChessBoardScene(QObject* parent = nullptr);
    void setBoardData(const QStringList& data, int rows, int cols);
    QStringList getBoardData() const { return boardData; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    void highlightArea(const QPoint& start, const std::vector<std::vector<bool>>& visited, int maxArea);

private:
    QMap<QString, QBrush> colorMap;
    QStringList boardData; // 存储棋盘数据
    int rows; // 行数
    int cols; // 列数
    std::vector<std::vector<QGraphicsRectItem*>> items; // 存储QGraphicsRectItem对象
    void initializeColors();
    void drawBoard(const QStringList& data, int rows, int cols);
    void highlightCell(int x, int y, const QBrush& brush);
};

#endif // CHESSBOARDSCENE_H