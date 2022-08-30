#pragma	once

class QMouseEvent;
class QKeyEvent;

class BaseOperator  
{
public:
	BaseOperator() = default;
	virtual void keyPressEvent(QKeyEvent* event) {}
	virtual void mousePressEvent(QMouseEvent* event) {}
	virtual void mouseMoveEvent(QMouseEvent* event) {}
	virtual void mouseReleaseEvent(QMouseEvent* event) {}

};
