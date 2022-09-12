#pragma once
#include <QObject>
#include <QPointF>
#include <QVector>
#include <QMap>

class BaseOperator;
class QWidget;

class DisplayManager : public QObject
{
    Q_OBJECT

public:
	static DisplayManager& instance()
	{
		static DisplayManager mgr;
		return mgr;
	}

	// Return viewport id and graphic widget.
	std::pair<int, QWidget*> createGraphicsWidget(QWidget* parent);
	QWidget* getGraphicsWidgetByViewportID(int vp) const;
	int      getViewportIDByGraphicsWidget(QWidget* w) const;

	void setCurrentOperator(int vp, const std::shared_ptr<BaseOperator>& op);

	std::uintptr_t addLine(int vp, const QPointF& p1, const QPointF& p2);
	void    modifyLine(int vp, std::uintptr_t key, const QPointF& p1, const QPointF& p2);

	std::uintptr_t addCircle(int vp, const QPointF& p, double r);
    void    modifyCircle(int vp, std::uintptr_t key, const QPointF& p, double r);

	std::uintptr_t addRect(int vp, const QPointF& topLeft, double w, double h);
    void    modifyRect(int vp, std::uintptr_t key, const QPointF& topLeft, double w, double h);

	std::uintptr_t addPolygon(int vp, const QVector<QPointF>& pts);
    void    modifyPolygon(int vp, std::uintptr_t key, const QVector<QPointF>& pts);

    void deleteItem(int vp, std::uintptr_t key);

	QPointF worldToViewport(int vp, const QPointF& p) const;
    QPointF viewportToWorld(int vp, const QPointF& p) const;

	QPointF getMousePointInWorld(int vp) const;

Q_SIGNALS:
	void signal_mousePos(int vp, const QPointF& pos);

private:
    DisplayManager()                                           = default;
    DisplayManager(const DisplayManager& other)                = delete;
    DisplayManager(DisplayManager&& other) noexcept            = delete;
    DisplayManager& operator=(const DisplayManager& other)     = delete;
    DisplayManager& operator=(DisplayManager&& other) noexcept = delete;

	QMap<int, QWidget*> m_vp2GraphicsWidget;
	QMap<int, QVector<std::uintptr_t>> m_vp2items;
};
