#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H

#pragma once
#include "Action.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

//Add Circle Action class
class AddCircAction : public Action
{
private:
	Point P1, P2; //Center and point on the circle
	GfxInfo CircGfxInfo;
	CFigure* Saved_Redo;
public:
	AddCircAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual bool Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~AddCircAction();
};

#endif