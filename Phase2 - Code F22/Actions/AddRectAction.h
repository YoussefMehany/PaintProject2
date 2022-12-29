#pragma once
#include "Action.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

//Add Rectangle Action class
class AddRectAction: public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
	CFigure* Saved_Redo;
public:
	AddRectAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual bool Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~AddRectAction();
};
