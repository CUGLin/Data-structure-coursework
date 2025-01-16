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
	void on_comboBox_currentIndexChanged(int index); // 槽函数，响应组合框选项变化

public:
	AddVertexDialog(QWidget *parent = nullptr);
	~AddVertexDialog();

	VertexType getType(); // 获取用户选择的顶点类型
	QString getName(); // 获取用户输入的名称
	QString getCategory(); // 获取用户输入的分类

private:
	Ui::AddVertexDialogClass *ui;
};
