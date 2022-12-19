#include "Action.h"
#include "../ApplicationManager.h"
class ChangeColorAction :public Action
{
	color colour;
public:
	ChangeColorAction(ApplicationManager* pApp, color clr,ActionType Act);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};
