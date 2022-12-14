#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class Circle;
class CoordConverter;

class CircleOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	CircleOperator();
	~CircleOperator() override = default;

    CircleOperator(const CircleOperator& other)                = delete;
    CircleOperator(CircleOperator&& other) noexcept            = delete;
    CircleOperator& operator=(const CircleOperator& other)     = delete;
    CircleOperator& operator=(CircleOperator&& other) noexcept = delete;

    void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;


	void reset() override;
private:

	QPointF m_centerPoint1;
	bool m_centerPoint1Created = false;
	std::uintptr_t m_previewCircle = 0;
};
