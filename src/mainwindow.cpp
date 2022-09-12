#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>

#include "DisplayManager/DisplayManager.h"
#include "Operator/CADOperatorMgr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DisplayManager& dm = DisplayManager::instance();
	auto [vp, graphicsView] = dm.createGraphicsWidget(ui->centralwidget);
	graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
	ui->verticalLayout->addWidget(graphicsView);
	setMouseTracking(true);
	centralWidget()->setMouseTracking(true);
	
	setWindowTitle("Fluent2D");
	resize(1200, 900);

	connect(&dm, &DisplayManager::signal_mousePos, this, &MainWindow::slot_printMousePos);

    CADOperatorMgr* pCADMgr = CADOperatorMgr::instance();
	pCADMgr->setCurrentViewport(vp);
	auto pCADActions = pCADMgr->getAllActions();
    for (auto&& p_cad_action : pCADActions)
    {
		ui->toolBar->addAction(p_cad_action);
    }

	QAction* clear = new QAction("clear", this);
	ui->toolBar->addAction(clear);

    QAction* zoomFit = new QAction("zoom fit", this);
	ui->toolBar->addAction(zoomFit);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::slot_printMousePos(const int vp, const QPointF& pos)
{
	ui->statusbar->showMessage(QString("Viewport%1  X:%2 Y:%3").arg(vp).arg(pos.x()).arg(pos.y()));
}
