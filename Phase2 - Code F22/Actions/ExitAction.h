#include "Action.h"
#include "../ApplicationManager.h"
class ExitAction :public Action
{
public:
	ExitAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
};

