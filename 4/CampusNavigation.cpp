#include "CampusNavigation.h"

CampusNavigation::CampusNavigation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CampusNavigationClass())
	, mCampusNavigationThread(new CampusNavigationThread()) // ����ͼ����
	, mpView(new CampusNavigationView()) // �Զ�����ͼ
{
    ui->setupUi(this);
	ui->centralWidget->layout()->addWidget(mpView);

	QSize windowSize = this->size();
	this->mpScene = new QGraphicsScene(0, 0, windowSize.width(), windowSize.height()); // ��ʼ������
	this->mSceneRect = this->mpScene->sceneRect(); // ��ȡ������������
	this->maxWidth = mSceneRect.width() > mSceneRect.height() ? mSceneRect.width() : mSceneRect.height(); // ��ȡ�������ά��
	this->mpView->setScene(mpScene); // �������󶨵���ͼ
	
	// ��������¼��ź����
	connect(mpView, &CampusNavigationView::mouseClicked, this, &CampusNavigation::mouseClicked);
	connect(mpView, &CampusNavigationView::mouseMoved, this, &CampusNavigation::mouseMoved);
}

CampusNavigation::~CampusNavigation()
{
    delete ui;
    delete mpScene;
	delete mpView;
	delete mCampusNavigationThread;
}

// ������¼���������״̬������ͬ����Ϊ
void CampusNavigation::mouseClicked(QPointF pt)
{
	switch (mState)
	{
	case State::None:
		break;
	case State::AddVertex:
		mousePressEventAddVertex(pt); // ��Ӷ���
		break;
	case State::AddEdge:
		mousePressEventAddEdge(pt); // ��ӱ�
		break;
	case State::CalculatePath:
		mousePressEventCalculatePaths(pt); // ����·��
		break;
	default:
		break;
	}
}

// ����ƶ��¼�������ʾ��ǰ���λ�û�ڵ���Ϣ
void CampusNavigation::mouseMoved(QPointF pt)
{
	QGraphicsEllipseItem* item = getEllipseItemFromScenePt(pt); // ��ȡ�������λ�õĽڵ�
	if (item != nullptr)
	{
		VertexData data = item->data(0).value<VertexData>(); // ��ȡ��������
		QString x = QString::number(data.x, 'f', 2);
		QString y = QString::number(data.y, 'f', 2);
		if (data.type == VertexType::Site) // �����վ��
		{
			QString name = QString::fromStdString(data.name);
			QString category = QString::fromStdString(data.category);
			QString str = QStringLiteral("����:") + name + "  " + QStringLiteral("���:") + category + "  " + QStringLiteral("x����:") + x + "  " + QStringLiteral("y����:") + y;
			this->statusBar()->showMessage(str); // ��ʾ״̬����Ϣ
		}
		else // �������ͨ�ڵ�
		{
			QString str = QStringLiteral("x����:") + x + "  " + QStringLiteral("y����:") + y;
			this->statusBar()->showMessage(str);
		}
	}
	else
	{
		this->statusBar()->showMessage(""); // �����겻�ڽڵ��ϣ����״̬��
	}
}

// ���ļ��¼��ۣ����ر����ͼ����
void CampusNavigation::on_actionOpenFile_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, QStringLiteral("���ļ�"), "E:\\ScholarData\\CUGUndergraduate", QStringLiteral("json�ļ� (*.json)"));
	if (fileName.isEmpty())
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("���ļ�ʧ��"));
	else
	{
		mCampusNavigationThread->LoadGraph(fileName); // ����ͼ����
		GraphAdjList* graph = mCampusNavigationThread->getGraph();
		DrawGraph(graph); // ����ͼ��
	}
}

// �����ļ��¼��ۣ����浱ǰͼ����
void CampusNavigation::on_actionSaveFile_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(nullptr, QStringLiteral("�����ļ�"), "E:\\CUGUndergraduate", QStringLiteral("json�ļ� (*.json)"));
	if (fileName.isEmpty())
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�����ļ�ʧ��"));
	else
	{
		if (mCampusNavigationThread->SaveGraph(fileName)) // ����ͼ����
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�����ļ��ɹ�"));
		else
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�����ļ�ʧ��"));
	}
}

// ��Ӷ��㰴ť�ۺ���
void CampusNavigation::on_actionAddVertex_triggered()
{
	if (mState == State::AddVertex)
	{
		mState = State::None; // �л�����״̬
		this->setCursor(Qt::ArrowCursor);
		return;
	}
	mState = State::AddVertex;
	this->setCursor(Qt::CrossCursor); // ����ʮ�ֹ��
}

// ��ӱ߰�ť�ۺ���
void CampusNavigation::on_actionAddEdge_triggered()
{
	if (mState == State::AddEdge && mvScenePoints.empty())
	{
		mState = State::None;
		this->setCursor(Qt::ArrowCursor);
		return;
	}

	this->setCursor(Qt::CrossCursor);
	mState = State::AddEdge;
}

// ����·����ť�ۺ���
void CampusNavigation::on_actionCalculatePaths_triggered()
{
	if (mState == State::CalculatePath && mvScenePoints.empty())
	{
		mState = State::None;
		this->setCursor(Qt::ArrowCursor);
		return;
	}

	this->setCursor(Qt::CrossCursor);
	mState = State::CalculatePath;
}

// �Ŵ���
void CampusNavigation::on_actionZoomIn_triggered()
{
	mpView->scale(1.2, 1.2); // ������ͼ
}

// ��С����
void CampusNavigation::on_actionZoomOut_triggered()
{
	mpView->scale(0.8, 0.8); // ��С��ͼ
}

// ��������ͼ����������ͱ�
bool CampusNavigation::DrawGraph(GraphAdjList* graph)
{
	if (graph == nullptr)
		return false;

	mpScene->clear(); // ��յ�ǰ����

	this->mSceneRect = graph->getBoundingRect(); // ��ȡͼ�ı߽����

	this->maxWidth = mSceneRect.width() > mSceneRect.height() ? mSceneRect.width() : mSceneRect.height(); // ȷ�����ߴ�


	QPen pen(Qt::red);
	QBrush brush(Qt::red);
	QPen pen2(Qt::black);
	pen.setWidth(maxWidth / 50);
	pen2.setWidth(maxWidth / 50);

	// �������нڵ�
	for (int i = 0; i < graph->NumberOfVertices(); i++)
	{
		const Vertexf* vertex = graph->getVertex(i);
		DrawVertex(vertex, maxWidth / 50, pen, brush); // ���Ƶ�������
	}

	// �������б�
	for (int i = 0; i < graph->NumberOfVertices(); i++)
	{
		const Vertexf* vertex = graph->getVertex(i);
		if (vertex == nullptr)
			continue;
		DrawVertexLinkEdges(vertex, graph, pen2); // ������ڵ������ı�
	}

	mpView->fitInView(mSceneRect, Qt::KeepAspectRatio); // ��Ӧ��ͼ��������С
	return true;
}

bool CampusNavigation::DrawVertex(const Vertexf* vertex, float size, QPen pen, QBrush brush)
{
	if (vertex == nullptr)
		return false;
	float halfSize = size / 2.0f;
	VertexData data = vertex->data;

	if (data.type == VertexType::RoadNode)
	{
		//���û���͸����Ϊ70%
		QColor color = pen.color();
		color.setAlphaF(0.3);
		pen.setColor(color);
		brush.setColor(color);
	}
	QGraphicsEllipseItem* item = mpScene->addEllipse(data.x - halfSize, data.y - halfSize, size, size, pen, brush);
	item->setData(0, QVariant::fromValue(data));	//���涥������

	// ��Ӷ���������Ϊ�ı�
	if (data.type == VertexType::Site) {
		QString name = QString::fromStdString(data.name);
		QGraphicsTextItem* textItem = mpScene->addText(name);
		textItem->setDefaultTextColor(Qt::green);
		// ���������С
		QFont font;
		font.setPointSize(20); // ���������СΪ20
		textItem->setFont(font);

		textItem->setPos(data.x + halfSize, data.y + halfSize);  // �����ı�λ��
	}

	return true;
}

bool CampusNavigation::DrawVertexLinkEdges(const Vertexf* vertex,GraphAdjList* graph, QPen pen)
{
	if (vertex == nullptr)
		return false;

	// ���ñߵ�͸����Ϊ 50%
	QColor penColor = pen.color();
	penColor.setAlpha(127);  // ����͸����Ϊ 50%��255 ��һ�룩
	pen.setColor(penColor);  // ���޸ĺ����ɫ���ûر�

	Edgef* edge = vertex->adj;
	while (edge!= nullptr)
	{
		const Vertexf* destVertex = graph->getVertex(edge->dest);
		if (destVertex == nullptr)
			continue;

		VertexData data = destVertex->data;
		QGraphicsLineItem* item=  mpScene->addLine(vertex->data.x, vertex->data.y, data.x, data.y, pen);
		item->setFlag(QGraphicsItem::ItemIsSelectable, false);	//����ѡ��
		// ����ߵ��е�����
		float midX = (vertex->data.x + data.x) / 2;
		float midY = (vertex->data.y + data.y) / 2;

		// ��ӱߵĳ�����Ϊ�ı�
		QString lengthText = QString::number(edge->cost, 'f', 2);  // ������λС��
		QGraphicsTextItem* textItem = mpScene->addText(lengthText);
		textItem->setDefaultTextColor(Qt::blue);
		// ���������С
		QFont font;
		font.setPointSize(20); // ���������СΪ20
		textItem->setFont(font);
		textItem->setPos(midX, midY);  // �����ı�λ��
		edge = edge->link;
	}
	return true;
}

void CampusNavigation::mousePressEventAddVertex(QPointF pt)
{

	AddVertexDialog dialog;
	dialog.show();

	if (dialog.exec() == QDialog::Accepted)
	{
		VertexData data;
		VertexType type = dialog.getType();
		data.type = type;
		switch (type)
		{
		case VertexType::None:
			break;
		case VertexType::Site:
			data.name = dialog.getName().toStdString();
			data.category = dialog.getCategory().toStdString();
			data.index = this->mCampusNavigationThread->getGraph()->NumberOfSites();
			break;
		case VertexType::RoadNode:
			data.index = this->mCampusNavigationThread->getGraph()->NumberOfRoadNodes();
			break;
		default:
			break;
		}
		data.x = pt.x();
		data.y = pt.y();

		GraphAdjList* graph = mCampusNavigationThread->getGraph();
		graph->insertVertex(data);
		const Vertexf* vertex = graph->getVertex(graph->NumberOfVertices() - 1);
		QPen pen(Qt::red);
		QBrush brush(Qt::red);
		pen.setWidth(maxWidth / 50);
		DrawVertex(vertex, maxWidth / 50, pen, brush);
	}
}

void CampusNavigation::mousePressEventAddEdge(QPointF pt)
{
	if (mvScenePoints.size() == 1)
	{
		QGraphicsEllipseItem* itemFirst = getEllipseItemFromScenePt(pt);
		QGraphicsEllipseItem* itemSecond = getEllipseItemFromScenePt(mvScenePoints[0]);
		if (itemFirst != nullptr && itemSecond != nullptr)
		{
			VertexData dataFirst = itemFirst->data(0).value<VertexData>();
			VertexData dataSecond = itemSecond->data(0).value<VertexData>();
			GraphAdjList* graph = mCampusNavigationThread->getGraph();
			int startVertexIndex = graph->getVertexPos(dataFirst);
			int endVertexIndex = graph->getVertexPos(dataSecond);

			float cost = QInputDialog::getDouble(this, QStringLiteral("����ߵ�Ȩֵ"), QStringLiteral("Ȩ��:"), 0, std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), 2);

			graph->insertEdge(startVertexIndex, endVertexIndex, cost);

			QPen pen(Qt::black);
			pen.setWidth(maxWidth / 70);
			DrawVertexLinkEdges(graph->getVertex(startVertexIndex), graph,pen);
		}
		mvScenePoints.clear();
	}
	else
	{
		mvScenePoints.push_back(pt);
	}
}

void CampusNavigation::mousePressEventCalculatePaths(QPointF pt)
{
	if (mvScenePoints.size() == 1)
	{
		if (mpPathItem != nullptr)
		{
			mpView->scene()->removeItem(mpPathItem);
			mpPathItem = nullptr;
			delete mpPathItem;
		}

		QGraphicsEllipseItem* itemFirst = getEllipseItemFromScenePt(pt);
		QGraphicsEllipseItem* itemSecond = getEllipseItemFromScenePt(mvScenePoints[0]);
		if (itemFirst != nullptr && itemSecond != nullptr)
		{
			VertexData dataFirst = itemFirst->data(0).value<VertexData>();
			VertexData dataSecond = itemSecond->data(0).value<VertexData>();
			GraphAdjList* graph = mCampusNavigationThread->getGraph();
			int startVertexIndex = graph->getVertexPosByDataIndex(dataFirst.index, dataFirst.type);
			int endVertexIndex = graph->getVertexPosByDataIndex(dataSecond.index, dataSecond.type);

			map<int, DjikstraPathsAndCost> S_vertexPosAndCost;
			mCampusNavigationThread->Dijkstra(startVertexIndex, S_vertexPosAndCost);

			DjikstraPathsAndCost pathAndCost = S_vertexPosAndCost[endVertexIndex];
			if (pathAndCost.cost == std::numeric_limits<float>::max())
			{
				QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("û���ҵ�·��"));
			}
			else
			{
				QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�ҵ�·��"));
				QPen pen(Qt::blue);
				pen.setWidth(maxWidth / 50);

				QPainterPath path;
				const Vertexf* vertexFirst = graph->getVertex(startVertexIndex);
				path.moveTo(vertexFirst->data.x, vertexFirst->data.y);
				for (int i = 0; i < pathAndCost.pathIndex.size(); i++)
				{
					const Vertexf* vertex = graph->getVertex(pathAndCost.pathIndex[i]);
					path.lineTo(vertex->data.x, vertex->data.y);
				}
				QGraphicsPathItem* pathItem = mpScene->addPath(path, pen);
				pathItem->setFlag(QGraphicsItem::ItemIsSelectable, false);	//����ѡ��
				mpPathItem = pathItem;
			}
		}
		mvScenePoints.clear();
	}
	else
	{
		mvScenePoints.push_back(pt);
	}
}

QGraphicsEllipseItem* CampusNavigation::getEllipseItemFromScenePt(QPointF pt)
{
	QGraphicsItem* item = mpScene->itemAt(pt, QTransform());
	if (item == nullptr)
		return nullptr;
	if (item->type() != QGraphicsEllipseItem::Type)
		return nullptr;
	return (QGraphicsEllipseItem*)item;

}

CampusNavigationView::CampusNavigationView()
{
	this->setMouseTracking(true);
}
CampusNavigationView::~CampusNavigationView()
{

}

void CampusNavigationView::mousePressEvent(QMouseEvent* event)
{
	QPointF pt = this->mapToScene(event->pos());
	emit mouseClicked(pt);
}

void CampusNavigationView::mouseMoveEvent(QMouseEvent* event)
{
	QPointF pt = this->mapToScene(event->pos());
	emit mouseMoved(pt);
}