#include "Action.h"
#include "../ApplicationManager.h"
class PlayRecAction :public Action
{
public:
	PlayRecAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};