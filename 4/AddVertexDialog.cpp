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

// �ۺ���������Ͽ�ĵ�ǰ���������仯ʱ������
// ���� index ��ʾ��Ͽ�ĵ�ǰ����
void AddVertexDialog::on_comboBox_currentIndexChanged(int index)
{
	switch (index)
	{
	case 0: // �������Ϊ0��ѡ��Site�����ͣ�
		ui->lineEditName->setEnabled(true);       // �������������
		ui->lineEditCategory->setEnabled(true);  // ���÷��������
		break;
	case 1: // �������Ϊ1��ѡ��RoadNode�����ͣ�
		ui->lineEditName->setEnabled(false);      // �������������
		ui->lineEditCategory->setEnabled(false); // ���÷��������
		break;
	default: // �����������������
		break;
	}
}

// ��ȡ�û�������������е�����
// ����ֵ�������ַ���
QString AddVertexDialog::getName()
{
	return ui->lineEditName->text();
}

// ��ȡ�û��ڷ���������е�����
// ����ֵ�������ַ���
QString AddVertexDialog::getCategory()
{
	return ui->lineEditCategory->text();
}

// ��ȡ�û�����Ͽ���ѡ��Ķ�������
// ����ֵ���������ͣ�VertexTypeö��ֵ��
VertexType AddVertexDialog::getType()
{
	int currentIndex = ui->comboBox->currentIndex(); // ��ȡ��Ͽ�ĵ�ǰ����
	switch (currentIndex)
	{
	case 0: // �������Ϊ0
		return VertexType::Site; // ����վ������
	case 1: // �������Ϊ1
		return VertexType::RoadNode; // ����·�ڵ�����
	default: // �������
		return VertexType::None; // ����������
	}
}