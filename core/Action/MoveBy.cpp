#include "..\e2daction.h"


e2d::MoveBy::MoveBy(double duration, Vector vector)
	: ActionGradual(duration)
{
	_deltaPos = vector;
}

e2d::MoveBy * e2d::MoveBy::create(double duration, Vector vector)
{
	return Create<MoveBy>(duration, vector);
}

void e2d::MoveBy::_init()
{
	ActionGradual::_init();

	if (_target)
	{
		_startPos = _target->getPos();
	}
}

void e2d::MoveBy::_update()
{
	ActionGradual::_update();

	if (_target)
	{
		_target->setPos(_startPos + _deltaPos * _delta);
	}
}

e2d::MoveBy * e2d::MoveBy::clone() const
{
	return Create<MoveBy>(_duration, _deltaPos);
}

e2d::MoveBy * e2d::MoveBy::reverse() const
{
	return Create<MoveBy>(_duration, -_deltaPos);
}