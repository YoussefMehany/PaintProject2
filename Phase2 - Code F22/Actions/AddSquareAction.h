#pragma once
#include "Action.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

//Add Square Action class
class AddSquareAction : public Action
{
private:
	Point P1; //Square Corners
	GfxInfo SquareGfxInfo;
	CFigure* Saved_Redo;
public:
	AddSquareAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual bool Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
	virtual void UndoActions();
	virtual void RedoActions();
	void ClearSaved();
	~AddSquareAction();
};
