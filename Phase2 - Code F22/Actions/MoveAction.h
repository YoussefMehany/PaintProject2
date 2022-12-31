#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
class MoveAction :public Action
{
private:
	Point P;
	CFigure* Saved;
	CFigure* Saved_Redo;
public:
	MoveAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
	virtual bool CanBeDeleted()  const;
	virtual void UndoActions();
	virtual void RedoActions();
	void ClearSaved();
	~MoveAction();
};
