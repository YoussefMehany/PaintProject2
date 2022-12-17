#include "Action.h"
#include "../ApplicationManager.h"

class UndoAction : public Action
{
private:
	ActionType Reverse_Last_Action;
public:

	UndoAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute() ;











};
