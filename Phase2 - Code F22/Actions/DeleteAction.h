#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
class DeleteAction :public Action
{
	CFigure* Saved;
	CFigure* Saved_Redo;
public:
	DeleteAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~DeleteAction();
};
