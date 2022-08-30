#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
private:
    Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:

	Ui::MainWindow *ui;
	int m_testIndex = 0;

private slots:
	void slot_printMousePos(const int vp, const QPointF& pos);
};
