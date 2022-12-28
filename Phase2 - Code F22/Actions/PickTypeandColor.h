#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CHexagon.h"

class PickTypeandColor :public Action
{
	Output* pOut;
	Input* pIn;
	shape FigType;
	string color;
	Point P;
	int CCounter;
	int FCounter;
	int Random;
public:
	PickTypeandColor(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	string TypetoString(shape);
	virtual bool CanBeRecorded() const;
};