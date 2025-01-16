#pragma once
#include <QDialog>
#include "ui_AddVertexDialog.h"
#include"AllStruct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddVertexDialogClass; };
QT_END_NAMESPACE


class AddVertexDialog : public QDialog
{
	Q_OBJECT

public slots:
	void on_comboBox_currentIndexChanged(int index); // �ۺ�������Ӧ��Ͽ�ѡ��仯

public:
	AddVertexDialog(QWidget *parent = nullptr);
	~AddVertexDialog();

	VertexType getType(); // ��ȡ�û�ѡ��Ķ�������
	QString getName(); // ��ȡ�û����������
	QString getCategory(); // ��ȡ�û�����ķ���

private:
	Ui::AddVertexDialogClass *ui;
};
