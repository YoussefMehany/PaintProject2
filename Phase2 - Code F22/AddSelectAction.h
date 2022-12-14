#include "Actions/Action.h"
#include "ApplicationManager.h"
class AddSelectAction :public Action
{
private:
	Point P;

public:
	AddSelectAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};

