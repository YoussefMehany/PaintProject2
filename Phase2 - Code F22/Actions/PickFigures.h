#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CHexagon.h"
class PickFigures :public Action
{
	Output* pOut;
	Input* pIn;
	shape FigType;
	Point P;
	int CCounter;
	int FCounter;
	int Random;
public:
	PickFigures(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute(bool ReadParams = true);
	string TypetoString(shape);
	virtual bool CanBeRecorded() const;
};
