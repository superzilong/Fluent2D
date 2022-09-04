#pragma	once
#include <qpoint.h>
#include "CADOperator.h"


class RectOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	RectOperator();
	~RectOperator() override = default;

    RectOperator(const RectOperator& other)                = delete;
    RectOperator(RectOperator&& other) noexcept            = delete;
    RectOperator& operator=(const RectOperator& other)     = delete;
    RectOperator& operator=(RectOperator&& other) noexcept = delete;

    void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void reset() override;
private:
    QPointF        m_rectPoint1;
    bool           m_rectPoint1Created = false;
    std::uintptr_t m_previewRect       = 0;
};
