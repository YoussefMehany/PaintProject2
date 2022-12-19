#include "Action.h"
#include "../ApplicationManager.h"
class MoveAction :public Action
{
private:
	Point P;
	Point P_Rec;
	Point P_Undo;
public:
	MoveAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};
