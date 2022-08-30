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
	QWidget* getGraphicsWidgetByViewportID(const int vp) const;
	int      getViewportIDByGraphicsWidget(QWidget* w) const;

	void setCurrentOperator(const int vp, const std::shared_ptr<BaseOperator>& op);

	std::uintptr_t addCircle(const int vp, const QPointF p, const double r);
    void    modifyCircle(const int vp, const std::uintptr_t key, const QPointF p, const double r);

	std::uintptr_t addRect(const int vp, const QPointF topLeft, const double w, const double h);
    void    modifyRect(const int vp, const std::uintptr_t key, const QPointF topLeft, const double w, const double h);

	std::uintptr_t addPolygon(const int vp, const QVector<QPointF>& pts);
    void    modifyPolygon(const int vp, const std::uintptr_t key, const QVector<QPointF>& pts);

    void deleteItem(const int vp, const std::uintptr_t key);

	QPointF worldToViewport(const int vp, const QPointF& p) const;
    QPointF viewportToWorld(const int vp, const QPointF& p) const;

Q_SIGNALS:
	void signal_mousePos(const int vp, const QPointF& pos);

private:
	DisplayManager() = default;
	DisplayManager(const DisplayManager& other) = default;
	DisplayManager(DisplayManager&& other) noexcept = default;
	DisplayManager& operator=(const DisplayManager& other) = default;
	DisplayManager& operator=(DisplayManager&& other) noexcept = default;

	QMap<int, QWidget*> m_vp2GraphicsWidget;
	QMap<int, QVector<std::uintptr_t>> m_vp2items;
};
