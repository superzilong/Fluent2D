#pragma once

#include <QGraphicsView>

class BaseOperator;

class GraphicWidget : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicWidget(QWidget* parent);

	std::shared_ptr<BaseOperator> getCurrentOperator() { return m_operator; }
	void setCurrentOperator(const std::shared_ptr<BaseOperator>& op) { m_operator = op; };

	QPointF worldToViewport(const QPointF& p) const;
	QPointF viewportToWorld(const QPointF& p) const;

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
	void init();
	void tick();

	std::shared_ptr<BaseOperator> m_operator;
	QGraphicsScene m_scene;

	QVector< QGraphicsLineItem*> m_bgGrid;

};



