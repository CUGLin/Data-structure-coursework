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
    QStringList boardData; // �洢��������
    int rows; // ����
    int cols; // ����
    std::vector<std::vector<QGraphicsRectItem*>> items; // �洢QGraphicsRectItem����
    void initializeColors();
    void drawBoard(const QStringList& data, int rows, int cols);
    void highlightCell(int x, int y, const QBrush& brush);
};

#endif // CHESSBOARDSCENE_H