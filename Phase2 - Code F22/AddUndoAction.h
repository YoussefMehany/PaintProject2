#include "Actions/Action.h"
#include "ApplicationManager.h"

class AddUndoAction: public Action
{
	enum{ MaxUndoCount = 5 };	//Max no of undo operation
private:
	ActionType reverse_last_action;
	int undo_action_count;
public:

	AddUndoAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute() ;











};
