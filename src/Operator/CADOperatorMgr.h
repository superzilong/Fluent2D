#include "CADOperator.h"

class CADOperatorMgr: public QObject
{
public:
	Q_OBJECT

public:
	static CADOperatorMgr* instance()
	{
		static CADOperatorMgr s_mgr;
		return &s_mgr;
	}

	std::vector<QAction*> getAllActions();
	CADOperatorSP         getCurrentOp();;
	void                  setCurrentViewport(int vp);

protected:
    CADOperatorMgr();
    ~CADOperatorMgr()                                          = default;
    CADOperatorMgr(const CADOperatorMgr& other)                = default;
    CADOperatorMgr(CADOperatorMgr&& other) noexcept            = default;
    CADOperatorMgr& operator=(const CADOperatorMgr& other)     = default;
    CADOperatorMgr& operator=(CADOperatorMgr&& other) noexcept = default;

private:
	std::vector<CADOperatorSP> m_operators;
	CADOperatorSP m_currentOp = nullptr;
	int m_currentVP = -1;

private slots:
	void slot_activateOperator(CADOperator* op);
	void slot_exitOperator(CADOperator* op);
};
