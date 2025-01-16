#include "CampusNavigation.h"

CampusNavigation::CampusNavigation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CampusNavigationClass())
	, mCampusNavigationThread(new CampusNavigationThread()) // 处理图操作
	, mpView(new CampusNavigationView()) // 自定义视图
{
    ui->setupUi(this);
	ui->centralWidget->layout()->addWidget(mpView);

	QSize windowSize = this->size();
	this->mpScene = new QGraphicsScene(0, 0, windowSize.width(), windowSize.height()); // 初始化场景
	this->mSceneRect = this->mpScene->sceneRect(); // 获取场景矩形区域
	this->maxWidth = mSceneRect.width() > mSceneRect.height() ? mSceneRect.width() : mSceneRect.height(); // 获取场景最大维度
	this->mpView->setScene(mpScene); // 将场景绑定到视图
	
	// 连接鼠标事件信号与槽
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

// 鼠标点击事件处理，根据状态触发不同的行为
void CampusNavigation::mouseClicked(QPointF pt)
{
	switch (mState)
	{
	case State::None:
		break;
	case State::AddVertex:
		mousePressEventAddVertex(pt); // 添加顶点
		break;
	case State::AddEdge:
		mousePressEventAddEdge(pt); // 添加边
		break;
	case State::CalculatePath:
		mousePressEventCalculatePaths(pt); // 计算路径
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理，显示当前鼠标位置或节点信息
void CampusNavigation::mouseMoved(QPointF pt)
{
	QGraphicsEllipseItem* item = getEllipseItemFromScenePt(pt); // 获取鼠标所在位置的节点
	if (item != nullptr)
	{
		VertexData data = item->data(0).value<VertexData>(); // 提取顶点数据
		QString x = QString::number(data.x, 'f', 2);
		QString y = QString::number(data.y, 'f', 2);
		if (data.type == VertexType::Site) // 如果是站点
		{
			QString name = QString::fromStdString(data.name);
			QString category = QString::fromStdString(data.category);
			QString str = QStringLiteral("名称:") + name + "  " + QStringLiteral("类别:") + category + "  " + QStringLiteral("x坐标:") + x + "  " + QStringLiteral("y坐标:") + y;
			this->statusBar()->showMessage(str); // 显示状态栏信息
		}
		else // 如果是普通节点
		{
			QString str = QStringLiteral("x坐标:") + x + "  " + QStringLiteral("y坐标:") + y;
			this->statusBar()->showMessage(str);
		}
	}
	else
	{
		this->statusBar()->showMessage(""); // 如果鼠标不在节点上，清空状态栏
	}
}

// 打开文件事件槽：加载保存的图数据
void CampusNavigation::on_actionOpenFile_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, QStringLiteral("打开文件"), "E:\\ScholarData\\CUGUndergraduate", QStringLiteral("json文件 (*.json)"));
	if (fileName.isEmpty())
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("打开文件失败"));
	else
	{
		mCampusNavigationThread->LoadGraph(fileName); // 加载图数据
		GraphAdjList* graph = mCampusNavigationThread->getGraph();
		DrawGraph(graph); // 绘制图形
	}
}

// 保存文件事件槽：保存当前图数据
void CampusNavigation::on_actionSaveFile_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(nullptr, QStringLiteral("保存文件"), "E:\\CUGUndergraduate", QStringLiteral("json文件 (*.json)"));
	if (fileName.isEmpty())
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("保存文件失败"));
	else
	{
		if (mCampusNavigationThread->SaveGraph(fileName)) // 保存图数据
			QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("保存文件成功"));
		else
			QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("保存文件失败"));
	}
}

// 添加顶点按钮槽函数
void CampusNavigation::on_actionAddVertex_triggered()
{
	if (mState == State::AddVertex)
	{
		mState = State::None; // 切换回无状态
		this->setCursor(Qt::ArrowCursor);
		return;
	}
	mState = State::AddVertex;
	this->setCursor(Qt::CrossCursor); // 设置十字光标
}

// 添加边按钮槽函数
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

// 计算路径按钮槽函数
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

// 放大功能
void CampusNavigation::on_actionZoomIn_triggered()
{
	mpView->scale(1.2, 1.2); // 缩放视图
}

// 缩小功能
void CampusNavigation::on_actionZoomOut_triggered()
{
	mpView->scale(0.8, 0.8); // 缩小视图
}

// 绘制整个图，包括顶点和边
bool CampusNavigation::DrawGraph(GraphAdjList* graph)
{
	if (graph == nullptr)
		return false;

	mpScene->clear(); // 清空当前场景

	this->mSceneRect = graph->getBoundingRect(); // 获取图的边界矩形

	this->maxWidth = mSceneRect.width() > mSceneRect.height() ? mSceneRect.width() : mSceneRect.height(); // 确定最大尺寸


	QPen pen(Qt::red);
	QBrush brush(Qt::red);
	QPen pen2(Qt::black);
	pen.setWidth(maxWidth / 50);
	pen2.setWidth(maxWidth / 50);

	// 绘制所有节点
	for (int i = 0; i < graph->NumberOfVertices(); i++)
	{
		const Vertexf* vertex = graph->getVertex(i);
		DrawVertex(vertex, maxWidth / 50, pen, brush); // 绘制单个顶点
	}

	// 绘制所有边
	for (int i = 0; i < graph->NumberOfVertices(); i++)
	{
		const Vertexf* vertex = graph->getVertex(i);
		if (vertex == nullptr)
			continue;
		DrawVertexLinkEdges(vertex, graph, pen2); // 绘制与节点相连的边
	}

	mpView->fitInView(mSceneRect, Qt::KeepAspectRatio); // 适应视图到场景大小
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
		//设置画笔透明度为70%
		QColor color = pen.color();
		color.setAlphaF(0.3);
		pen.setColor(color);
		brush.setColor(color);
	}
	QGraphicsEllipseItem* item = mpScene->addEllipse(data.x - halfSize, data.y - halfSize, size, size, pen, brush);
	item->setData(0, QVariant::fromValue(data));	//保存顶点数据

	// 添加顶点名称作为文本
	if (data.type == VertexType::Site) {
		QString name = QString::fromStdString(data.name);
		QGraphicsTextItem* textItem = mpScene->addText(name);
		textItem->setDefaultTextColor(Qt::green);
		// 设置字体大小
		QFont font;
		font.setPointSize(20); // 设置字体大小为20
		textItem->setFont(font);

		textItem->setPos(data.x + halfSize, data.y + halfSize);  // 设置文本位置
	}

	return true;
}

bool CampusNavigation::DrawVertexLinkEdges(const Vertexf* vertex,GraphAdjList* graph, QPen pen)
{
	if (vertex == nullptr)
		return false;

	// 设置边的透明度为 50%
	QColor penColor = pen.color();
	penColor.setAlpha(127);  // 设置透明度为 50%（255 的一半）
	pen.setColor(penColor);  // 将修改后的颜色设置回笔

	Edgef* edge = vertex->adj;
	while (edge!= nullptr)
	{
		const Vertexf* destVertex = graph->getVertex(edge->dest);
		if (destVertex == nullptr)
			continue;

		VertexData data = destVertex->data;
		QGraphicsLineItem* item=  mpScene->addLine(vertex->data.x, vertex->data.y, data.x, data.y, pen);
		item->setFlag(QGraphicsItem::ItemIsSelectable, false);	//不可选中
		// 计算边的中点坐标
		float midX = (vertex->data.x + data.x) / 2;
		float midY = (vertex->data.y + data.y) / 2;

		// 添加边的长度作为文本
		QString lengthText = QString::number(edge->cost, 'f', 2);  // 保留两位小数
		QGraphicsTextItem* textItem = mpScene->addText(lengthText);
		textItem->setDefaultTextColor(Qt::blue);
		// 设置字体大小
		QFont font;
		font.setPointSize(20); // 设置字体大小为20
		textItem->setFont(font);
		textItem->setPos(midX, midY);  // 设置文本位置
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

			float cost = QInputDialog::getDouble(this, QStringLiteral("输入边的权值"), QStringLiteral("权重:"), 0, std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), 2);

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
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("没有找到路径"));
			}
			else
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("找到路径"));
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
				pathItem->setFlag(QGraphicsItem::ItemIsSelectable, false);	//不可选中
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