#include "Actions/Action.h"
#include "ApplicationManager.h"
class AddMoveAction:public Action 
{
private:
	Point P;

public:
	AddMoveAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};
