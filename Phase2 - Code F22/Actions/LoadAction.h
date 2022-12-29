#pragma once
#include "Action.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CSquare.h"
#include<fstream>

class LoadAction :public Action
{
	ifstream InFile;
	string fileName;

public:
	LoadAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual bool Execute(bool ReadParams = true);
	void CreateFigure(string Word);
	color getColorr(string clr);
	virtual bool CanBeRecorded() const;
};
