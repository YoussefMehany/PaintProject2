#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"
class ApplicationManager; //forward class declaration
//Base class for all possible actions
class Action
{
protected:
	ApplicationManager* pManager;	//Actions needs AppMngr to do their job
	bool Recorded;
public:

	Action(ApplicationManager* pApp) //constructor
	{
		pManager = pApp;
		Recorded = false;
	}

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;

	//Execute action (code depends on action type)
	virtual bool Execute(bool = true) = 0;
	virtual void UndoActions() {};
	virtual void RedoActions() {};
	virtual void ClearSaved() {};
	void SetRecorded(bool B)
	{
		Recorded = B;
	}
	bool IsRecorded() const
	{
		return Recorded;
	}
	virtual bool CanBeRecorded() const = 0;
	virtual ~Action() {};
};

#endif