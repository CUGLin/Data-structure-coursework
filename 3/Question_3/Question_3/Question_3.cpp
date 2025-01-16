#include "Question_3.h"
#include <QApplication>
#include <QGraphicsView>
#include <QRadioButton>
#include "DecisionTree.h"
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <QDebug>

#define CHN(text) QString::fromLocal8Bit(text)

void loadSamplesFromCSV(std::vector<Sample>& samples);

Question_3::Question_3(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // 实例化一个画布场景并显示在页面上
    scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    // 连接算法切换信号和槽
    connect(ui.radioButton_10, &QRadioButton::toggled, this, &Question_3::updateAlgorithmType);
    connect(ui.radioButton_11, &QRadioButton::toggled, this, &Question_3::updateAlgorithmType);
}

Question_3::~Question_3()
{

}


// 获取 QGroupBox 中选中的 QRadioButton 的文本
QString Question_3::getSelectedRadio(QGroupBox* groupBox)
{
    QList<QRadioButton*> radioButtons = groupBox->findChildren<QRadioButton*>();
    for (QRadioButton* radioButton : radioButtons) {
        if (radioButton->isChecked()) {
            return radioButton->text(); // 返回选中按钮的文本
        }
    }
    return "NULL"; // 没有选中任何按钮
}

void Question_3::on_loadCsvButton_clicked()
{

    // 加载样本数据
    std::vector<Sample> samples;

    loadSamplesFromCSV(samples);

    if (samples.size() == 0)
    {
        return;
    }
    //// 构建决策树
    //DecisionTree dt;
    std::set<std::string> attributes = { "Weather", "Temperature", "Humidity", "Wind" };
    dt.root = dt.buildTree(samples, attributes);

    // 可视化
    //QGraphicsScene scene;
    scene->clear();
    dt.visualizeTree(scene, dt.root, 400, 50, 250, 100);

    ui.resultLabel->setText(CHN("请选择情况进行决策"));

}

void Question_3::on_analyzeButton_clicked()
{
    // 构造输入样本
    Sample inputSample =
    {
        getSelectedRadio(ui.groupBox_1).QString::toStdString(),  // 获取天气选项
        getSelectedRadio(ui.groupBox_2).QString::toStdString(),  // 获取温度选项
        getSelectedRadio(ui.groupBox_3).QString::toStdString(),  // 获取湿度选项
        getSelectedRadio(ui.groupBox_4).QString::toStdString(),  // 获取风力选项
        ""
    };

    if (getSelectedRadio(ui.groupBox_1).QString::toStdString() == "NULL" &&
        getSelectedRadio(ui.groupBox_2).QString::toStdString() == "NULL" &&
        getSelectedRadio(ui.groupBox_3).QString::toStdString() == "NULL" &&
        getSelectedRadio(ui.groupBox_4).QString::toStdString() == "NULL")
    {
        ui.resultLabel->setText(CHN("请先进行选择！"));
        return;
    }

    if (!dt.root)
    {
        ui.resultLabel->setText(CHN("请先输入CSV文件！"));
        return;
    }

    // 调用预测函数
    std::string result = dt.predict(inputSample, dt.root);

    ui.resultLabel->setText(result == "yes" ? CHN("Yes") : CHN("No"));

}

// 从 CSV 文件加载样本数据
void loadSamplesFromCSV( std::vector<Sample>& samples) 
{
    // 打开文件选择对话框
    QString filePath = QFileDialog::getOpenFileName
    (
        nullptr,
        QString::fromLocal8Bit("选择CSV文件"),
        "",
        "CSV File (*.csv)"
    );

    if (filePath.isEmpty())
    {
        qDebug() << "文件路径为空，取消加载。";
        return;
    }

    std::ifstream file(filePath.toStdString());
    if (!file.is_open()) {
        qDebug() << "无法打开文件: " << filePath;
        return;
    }

    std::string line;
    // 跳过表头
    std::getline(file, line);

    //qDebug() << "开始加载CSV数据...";
    // 逐行读取数据
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string weather, temperature, humidity, wind, date;

        // 读取每一列的数据
        std::getline(ss, weather, ',');
        std::getline(ss, temperature, ',');
        std::getline(ss, humidity, ',');
        std::getline(ss, wind, ',');
        std::getline(ss, date, ',');

        // 添加到样本集合
        samples.push_back({ weather, temperature, humidity, wind, date });

        //// 打印每条加载的数据
        //qDebug() << "加载样本: 天气: " << QString::fromStdString(weather)
        //    << ", 温度: " << QString::fromStdString(temperature)
        //    << ", 湿度: " << QString::fromStdString(humidity)
        //    << ", 风: " << QString::fromStdString(wind)
        //    << ", 日期: " << QString::fromStdString(date);
    }

    //qDebug() << "CSV数据加载完成，共加载样本数量: " << samples.size();
    file.close();
}

void Question_3::updateAlgorithmType() {
    if (ui.radioButton_10->isChecked()) {
        dt.algorithmType = ID3; // 切换为 ID3 算法
    }
    else if (ui.radioButton_11->isChecked()) {
        dt.algorithmType = C45; // 切换为 C4.5 算法
    }
    qDebug() << "当前算法已更新为:" << (dt.algorithmType == ID3 ? "ID3" : "C4.5");
}

