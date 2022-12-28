#include "Action.h"
#include "../ApplicationManager.h"

class UndoAction : public Action
{
private:
public:

	UndoAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
};
