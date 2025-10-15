#include "..\ebase.h"
#include "..\enodes.h"
#include "..\emanagers.h"
#include "..\etools.h"
#include "..\eactions.h"
#include <algorithm>

e2d::EScene::EScene()
	: m_bWillSave(true)
	, m_bSortNeeded(false)
	, m_pRoot(new ENode())
{
	m_pRoot->_onEnter();
	m_pRoot->_setParentScene(this);
	m_pRoot->_setSize(EApp::getWidth(), EApp::getHeight());
	m_pRoot->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
}

e2d::EScene::~EScene()
{
	SafeReleaseAndClear(&m_pRoot);
}

void e2d::EScene::onEnter()
{
}

void e2d::EScene::onExit()
{
}

bool e2d::EScene::onActivate()
{
	return true;
}

bool e2d::EScene::onInactive()
{
	return true;
}

bool e2d::EScene::onCloseWindow()
{
	return true;
}

void e2d::EScene::_onRender()
{
	m_pRoot->_callOn();
}

void e2d::EScene::add(ENode * child, int order /* = 0 */)
{
	m_pRoot->addChild(child, order);
}

bool e2d::EScene::remove(ENode * child, bool release /* = false */)
{
	return m_pRoot->removeChild(child, release);
}

void e2d::EScene::remove(const EString &childName, bool release /* = false */)
{
	return m_pRoot->removeChild(childName, release);
}

e2d::EVector<e2d::ENode*>& e2d::EScene::getChildren()
{
	return m_pRoot->m_vChildren;
}

size_t e2d::EScene::getChildrenCount() const
{
	return m_pRoot->getChildrenCount();
}

e2d::ENode * e2d::EScene::getChild(const EString &childName)
{
	return m_pRoot->getChild(childName);
}

e2d::ENode * e2d::EScene::getRoot() const
{
	return m_pRoot;
}

void e2d::EScene::clearAllChildren()
{
	m_pRoot->clearAllChildren();
}

void e2d::EScene::runAction(EAction * action)
{
	this->m_pRoot->runAction(action);
}