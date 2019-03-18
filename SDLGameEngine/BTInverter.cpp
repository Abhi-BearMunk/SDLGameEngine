#include "BTInverter.h"



BTInverter::BTInverter()
{
}


BTInverter::~BTInverter()
{
}

BTNode::BTState BTInverter::Update()
{
	if (child->Update() == BTState::Failure)
	{
		return BTState::Success;
	}
	else if (child->Update() == BTState::Success)
	{
		return BTState::Failure;
	}
	return BTState::Running;
}