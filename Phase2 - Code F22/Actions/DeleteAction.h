#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
class DeleteAction :public Action
{
	CFigure* Saved;
public:
	DeleteAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
	virtual bool CanBeDeleted()  const;
	virtual void UndoActions();
	virtual void RedoActions();
	void ClearSaved();
	~DeleteAction();
};
