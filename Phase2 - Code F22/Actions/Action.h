#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"
class ApplicationManager; //forward class declaration
//Base class for all possible actions
class Action
{
protected:
	ApplicationManager* pManager;	//Actions needs AppMngr to do their job
	int id;
	bool Recorded;
public:

	Action(ApplicationManager* pApp) { pManager = pApp; Recorded = false; }	//constructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;

	//Execute action (code depends on action type)
	virtual void Execute(bool = true) = 0;
	virtual void UndoActions() {};
	virtual void RedoActions() {};
	void SetRecorded(bool B) { Recorded = B; }
	bool IsRecorded() const
	{
		return Recorded;
	}
	virtual bool CanBeRecorded() const = 0;
};

#endif