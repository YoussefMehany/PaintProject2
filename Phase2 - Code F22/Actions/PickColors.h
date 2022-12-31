#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class PickColors :public Action
{
	Output* pOut;
	Input* pIn;
	string color;
	Point P;
	int CCounter;
	int FCounter;
	int Random;
public:
	PickColors(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
	virtual bool CanBeDeleted()  const;
	void Reset();
};
