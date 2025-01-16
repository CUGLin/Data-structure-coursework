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
    // ʵ����һ��������������ʾ��ҳ����
    scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    // �����㷨�л��źźͲ�
    connect(ui.radioButton_10, &QRadioButton::toggled, this, &Question_3::updateAlgorithmType);
    connect(ui.radioButton_11, &QRadioButton::toggled, this, &Question_3::updateAlgorithmType);
}

Question_3::~Question_3()
{

}


// ��ȡ QGroupBox ��ѡ�е� QRadioButton ���ı�
QString Question_3::getSelectedRadio(QGroupBox* groupBox)
{
    QList<QRadioButton*> radioButtons = groupBox->findChildren<QRadioButton*>();
    for (QRadioButton* radioButton : radioButtons) {
        if (radioButton->isChecked()) {
            return radioButton->text(); // ����ѡ�а�ť���ı�
        }
    }
    return "NULL"; // û��ѡ���κΰ�ť
}

void Question_3::on_loadCsvButton_clicked()
{

    // ������������
    std::vector<Sample> samples;

    loadSamplesFromCSV(samples);

    if (samples.size() == 0)
    {
        return;
    }
    //// ����������
    //DecisionTree dt;
    std::set<std::string> attributes = { "Weather", "Temperature", "Humidity", "Wind" };
    dt.root = dt.buildTree(samples, attributes);

    // ���ӻ�
    //QGraphicsScene scene;
    scene->clear();
    dt.visualizeTree(scene, dt.root, 400, 50, 250, 100);

    ui.resultLabel->setText(CHN("��ѡ��������о���"));

}

void Question_3::on_analyzeButton_clicked()
{
    // ������������
    Sample inputSample =
    {
        getSelectedRadio(ui.groupBox_1).QString::toStdString(),  // ��ȡ����ѡ��
        getSelectedRadio(ui.groupBox_2).QString::toStdString(),  // ��ȡ�¶�ѡ��
        getSelectedRadio(ui.groupBox_3).QString::toStdString(),  // ��ȡʪ��ѡ��
        getSelectedRadio(ui.groupBox_4).QString::toStdString(),  // ��ȡ����ѡ��
        ""
    };

    if (getSelectedRadio(ui.groupBox_1).QString::toStdString() == "NULL" &&
        getSelectedRadio(ui.groupBox_2).QString::toStdString() == "NULL" &&
        getSelectedRadio(ui.groupBox_3).QString::toStdString() == "NULL" &&
        getSelectedRadio(ui.groupBox_4).QString::toStdString() == "NULL")
    {
        ui.resultLabel->setText(CHN("���Ƚ���ѡ��"));
        return;
    }

    if (!dt.root)
    {
        ui.resultLabel->setText(CHN("��������CSV�ļ���"));
        return;
    }

    // ����Ԥ�⺯��
    std::string result = dt.predict(inputSample, dt.root);

    ui.resultLabel->setText(result == "yes" ? CHN("Yes") : CHN("No"));

}

// �� CSV �ļ�������������
void loadSamplesFromCSV( std::vector<Sample>& samples) 
{
    // ���ļ�ѡ��Ի���
    QString filePath = QFileDialog::getOpenFileName
    (
        nullptr,
        QString::fromLocal8Bit("ѡ��CSV�ļ�"),
        "",
        "CSV File (*.csv)"
    );

    if (filePath.isEmpty())
    {
        qDebug() << "�ļ�·��Ϊ�գ�ȡ�����ء�";
        return;
    }

    std::ifstream file(filePath.toStdString());
    if (!file.is_open()) {
        qDebug() << "�޷����ļ�: " << filePath;
        return;
    }

    std::string line;
    // ������ͷ
    std::getline(file, line);

    //qDebug() << "��ʼ����CSV����...";
    // ���ж�ȡ����
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string weather, temperature, humidity, wind, date;

        // ��ȡÿһ�е�����
        std::getline(ss, weather, ',');
        std::getline(ss, temperature, ',');
        std::getline(ss, humidity, ',');
        std::getline(ss, wind, ',');
        std::getline(ss, date, ',');

        // ��ӵ���������
        samples.push_back({ weather, temperature, humidity, wind, date });

        //// ��ӡÿ�����ص�����
        //qDebug() << "��������: ����: " << QString::fromStdString(weather)
        //    << ", �¶�: " << QString::fromStdString(temperature)
        //    << ", ʪ��: " << QString::fromStdString(humidity)
        //    << ", ��: " << QString::fromStdString(wind)
        //    << ", ����: " << QString::fromStdString(date);
    }

    //qDebug() << "CSV���ݼ�����ɣ���������������: " << samples.size();
    file.close();
}

void Question_3::updateAlgorithmType() {
    if (ui.radioButton_10->isChecked()) {
        dt.algorithmType = ID3; // �л�Ϊ ID3 �㷨
    }
    else if (ui.radioButton_11->isChecked()) {
        dt.algorithmType = C45; // �л�Ϊ C4.5 �㷨
    }
    qDebug() << "��ǰ�㷨�Ѹ���Ϊ:" << (dt.algorithmType == ID3 ? "ID3" : "C4.5");
}

