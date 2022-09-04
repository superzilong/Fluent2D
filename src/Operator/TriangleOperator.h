#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class TriangleOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	TriangleOperator();
	~TriangleOperator() override                                   = default;

    TriangleOperator(const TriangleOperator& other)                = delete;
    TriangleOperator(TriangleOperator&& other) noexcept            = delete;
    TriangleOperator& operator=(const TriangleOperator& other)     = delete;
    TriangleOperator& operator=(TriangleOperator&& other) noexcept = delete;

    void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void reset() override;
private:
    QPointF        m_point1;
    QPointF        m_point2;
    bool           m_point1Created = false;
    bool           m_point2Created = false;
    std::uintptr_t m_previewLine   = 0;
    std::uintptr_t m_previewTri    = 0;

};
