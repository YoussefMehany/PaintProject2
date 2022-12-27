#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
class PickFigures :public Action
{
	Output* pOut;
	Input* pIn;
	shape FigType;
	Point P;
	int CCounter;
	int FCounter;
public:
	PickFigures(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	string TypetoString(shape);
};
