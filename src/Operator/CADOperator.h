#pragma	once
#include <QAction>
#include <QObject>

#include "DisplayManager/BaseOperator.h"

class QMouseEvent;
class QKeyEvent;

class CADOperator : public QObject, public BaseOperator
{
public:
	Q_OBJECT

public:
	CADOperator();
	~CADOperator() = default;

	void     setViewport(const int vp) { m_vp = vp; }
	QAction* getAction() { return &m_action; }

	virtual void keyPressEvent(QKeyEvent* event) {}
	virtual void mousePressEvent(QMouseEvent* event) {}
	virtual void mouseMoveEvent(QMouseEvent* event) {}
	virtual void mouseReleaseEvent(QMouseEvent* event) {}
	virtual void reset() {}

protected:
    CADOperator(const CADOperator& other)                = default;
    CADOperator(CADOperator&& other) noexcept            = default;
    CADOperator& operator=(const CADOperator& other)     = default;
    CADOperator& operator=(CADOperator&& other) noexcept = default;

    QAction      m_action;
	int          m_vp;
	
signals:
	void signal_activate(CADOperator* op);
	void signal_exit(CADOperator* op);
};

inline CADOperator::CADOperator()
{
	m_action.setCheckable(true);
	connect(&m_action, &QAction::triggered, this, [this](bool bChecked)
	{
		if (bChecked)
		{
			emit signal_activate(this);
		}
		else
		{
			emit signal_exit(this);
		}
	});
}

using CADOperatorSP = std::shared_ptr<CADOperator>;
