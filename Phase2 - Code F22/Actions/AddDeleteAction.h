#include "Action.h"
#include "../ApplicationManager.h"
class AddDeleteAction :public Action
{
public:
	AddDeleteAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};
