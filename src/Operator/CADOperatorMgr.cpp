#include "CADOperatorMgr.h"

#include <memory>

#include "CircleOperator.h"
#include "RectOperator.h"
#include "TriangleOperator.h"

#include "DisplayManager/DisplayManager.h"

CADOperatorMgr::CADOperatorMgr()
{
	RectOperator* rectOp = new RectOperator();
	CircleOperator* circleOp = new CircleOperator();
	TriangleOperator* triOp = new TriangleOperator();
	m_operators.push_back(std::make_shared<RectOperator>());
	m_operators.push_back(std::make_shared<CircleOperator>());
	m_operators.push_back(std::make_shared<TriangleOperator>());
	for (auto&& op : m_operators)
	{
		connect(op.get(), &CADOperator::signal_activate, this, &CADOperatorMgr::slot_activateOperator);
		connect(op.get(), &CADOperator::signal_exit, this, &CADOperatorMgr::slot_exitOperator);
	}
}

std::vector<QAction*> CADOperatorMgr::getAllActions()
{
	std::vector<QAction*> actions;
	actions.reserve(m_operators.size());
	std::transform(m_operators.begin(), m_operators.end(), std::back_inserter(actions), [](const CADOperatorSP& op) { return op->getAction(); });
	return actions;
}

CADOperatorSP CADOperatorMgr::getCurrentOp()
{
    return m_currentOp;
}

void CADOperatorMgr::setCurrentViewport(int vp)
{
	m_currentVP = vp;
}

void CADOperatorMgr::slot_activateOperator(CADOperator* op)
{
	if (m_currentOp && m_currentOp.get() != op)
	{
		emit m_currentOp->signal_exit(m_currentOp.get());
	}

	auto iter = std::find_if(m_operators.begin(), m_operators.end(), [op](const CADOperatorSP& spOp) { return spOp.get() == op; });
	if (iter != m_operators.end())
	{
		m_currentOp = *iter;
		m_currentOp->setViewport(m_currentVP);
		DisplayManager::instance().setCurrentOperator(m_currentVP, m_currentOp);
	}
}

void CADOperatorMgr::slot_exitOperator(CADOperator* op)
{
	auto pAction = op->getAction();
	if (pAction->isChecked())
	{
		op->reset();
		pAction->blockSignals(true);
		pAction->setChecked(false);
		pAction->blockSignals(false);
		DisplayManager::instance().setCurrentOperator(m_currentVP, nullptr);
	}
	m_currentOp = nullptr;
}
