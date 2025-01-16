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

    connect(ui.LoadFile, &QPushButton::clicked, this, &Question_1::on_loadButton_clicked); // �����źźͲ�_��������
    connect(ui.SelectFile, &QPushButton::clicked, this, &Question_1::on_selectButton_clicked); // �����źźͲ�_��ʾ����
    connect(ui.ShowFile, &QPushButton::clicked, this, &Question_1::on_showButton_clicked); // �����źźͲ�_��ʾ����
}

Question_1::~Question_1()
{
    delete scene;  //��ʱ����ָ���ͷŻ���
}

void Question_1::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)")); // �����ļ�ѡ�񴰿�
    if (!fileName.isEmpty()) {
        loadBoardFromFile(fileName); // �����ļ�
        ui.FileLine->setText(fileName); // ��ʾ�ļ�·��
    }
}

void Question_1::loadBoardFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QStringList boardData;

    // ��ȡ���̳ߴ�
    QString line = in.readLine();
    QStringList sizeInfo = line.split(' ', QString::SkipEmptyParts);
    if (sizeInfo.size() != 2)
        return; // �ߴ���Ϣ������

    int rows = sizeInfo[0].toInt();
    int cols = sizeInfo[1].toInt();

    // ��ȡ��������
    for (int i = 0; i < rows; ++i) {
        line = in.readLine();
        if (line.length() != cols) // ȷ��ÿ�г���������ƥ��
            return;
        boardData.append(line);
    }
    file.close();

    scene->setBoardData(boardData, rows, cols);
}

void Question_1::on_selectButton_clicked()
{
    findMaxArea(); // �ҵ�����������򲢸���TextFile
}

void Question_1::on_showButton_clicked()
{
    highlightMaxArea(); // ������ʾ�����������
}

void Question_1::findMaxArea()
{
    QStringList boardData = scene->getBoardData(); // ��scene�л�ȡ��������
    int rows = scene->getRows();
    int cols = scene->getCols();
    if (boardData.isEmpty() || rows <= 0 || cols <= 0) {
        QMessageBox::warning(this, tr("Warning"), tr("Please load the board data first."));
        return;
    }

    int maxArea = 0;
    QChar maxColor; // ��¼����������ɫ
    QPoint maxAreaPosition(-1, -1);

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false)); // ������άvisited����

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited[i][j]) {
                QChar color = boardData[i].at(j); // ��ȡ��ɫ�ַ�
                int area = dfs(boardData, visited, i, j, color);
                if (area > maxArea) {
                    maxArea = area;
                    maxColor = color; // ��������������ɫ
                    maxAreaPosition = QPoint(i, j);
                }
            }
        }
    }

    // ��ʾ�������������������ɫ
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

    // ȫ�� visited ���飬���ڴ洢�������
    std::vector<std::vector<bool>> globalVisited(rows, std::vector<bool>(cols, false));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!globalVisited[i][j]) {
                // �ֲ� visited ���飬�����ڵ�ǰ DFS
                std::vector<std::vector<bool>> localVisited(rows, std::vector<bool>(cols, false));
                QChar color = boardData[i].at(j); // ��ȡ��ǰ���ӵ���ɫ
                int area = dfs(boardData, localVisited, i, j, color);
                if (area > maxArea) {
                    maxArea = area;
                    maxAreaPosition = QPoint(i, j);

                    // ����ȫ�� visited ����Ϊ��ǰ�������
                    globalVisited = localVisited;
                }
            }
        }
    }

    // ��������������ʾ
    scene->highlightArea(maxAreaPosition, globalVisited, maxArea);
}

int Question_1::dfs(const QStringList& boardData, std::vector<std::vector<bool>>& visited, int x, int y, const QString& color)
{
    if (x < 0 || x >= boardData.size() || y < 0 || y >= boardData[x].size() || visited[x][y] || boardData[x].at(y) != color) {
        return 0;
    }

    visited[x][y] = true; // ��ǵ�ǰ����Ϊ�ѷ���
    int area = 1; // ��ǰ������Ϊ���������һ����

    // �ݹ�ؼ���ĸ���������ڸ���
    area += dfs(boardData, visited, x + 1, y, color); // ��
    area += dfs(boardData, visited, x - 1, y, color); // ��
    area += dfs(boardData, visited, x, y + 1, color); // ��
    area += dfs(boardData, visited, x, y - 1, color); // ��

    return area;
}

