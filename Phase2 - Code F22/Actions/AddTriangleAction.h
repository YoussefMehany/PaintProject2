#pragma once
#include "Action.h"

#include "..\ApplicationManager.h"
//Add Triangle Action class
class AddTriangleAction : public Action
{
private:
	Point P1, P2, P3; //Triangle Corners
	GfxInfo TriangleGfxInfo;
	CFigure* Saved_Redo;
public:
	AddTriangleAction(ApplicationManager* pApp);

	//Reads Triangle parameters
	virtual void ReadActionParameters();

	//Add Triangle to the ApplicationManager
	virtual bool Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~AddTriangleAction();
};
