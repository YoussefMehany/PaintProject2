#include "Action.h"
#include "../ApplicationManager.h"
class AddChangeColorAction :public Action
{
	color colour;
public:
	AddChangeColorAction(ApplicationManager* pApp, color clr);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};
