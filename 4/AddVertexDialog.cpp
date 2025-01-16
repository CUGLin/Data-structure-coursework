#include "AddVertexDialog.h"

AddVertexDialog::AddVertexDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::AddVertexDialogClass())
{
	ui->setupUi(this);
}

AddVertexDialog::~AddVertexDialog()
{
	delete ui;
}

// 槽函数：当组合框的当前索引发生变化时被调用
// 参数 index 表示组合框的当前索引
void AddVertexDialog::on_comboBox_currentIndexChanged(int index)
{
	switch (index)
	{
	case 0: // 如果索引为0（选择“Site”类型）
		ui->lineEditName->setEnabled(true);       // 启用名称输入框
		ui->lineEditCategory->setEnabled(true);  // 启用分类输入框
		break;
	case 1: // 如果索引为1（选择“RoadNode”类型）
		ui->lineEditName->setEnabled(false);      // 禁用名称输入框
		ui->lineEditCategory->setEnabled(false); // 禁用分类输入框
		break;
	default: // 其他情况，不做处理
		break;
	}
}

// 获取用户在名称输入框中的输入
// 返回值：名称字符串
QString AddVertexDialog::getName()
{
	return ui->lineEditName->text();
}

// 获取用户在分类输入框中的输入
// 返回值：分类字符串
QString AddVertexDialog::getCategory()
{
	return ui->lineEditCategory->text();
}

// 获取用户在组合框中选择的顶点类型
// 返回值：顶点类型（VertexType枚举值）
VertexType AddVertexDialog::getType()
{
	int currentIndex = ui->comboBox->currentIndex(); // 获取组合框的当前索引
	switch (currentIndex)
	{
	case 0: // 如果索引为0
		return VertexType::Site; // 返回站点类型
	case 1: // 如果索引为1
		return VertexType::RoadNode; // 返回路节点类型
	default: // 其他情况
		return VertexType::None; // 返回无类型
	}
}