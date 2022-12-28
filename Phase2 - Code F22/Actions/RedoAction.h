#include "Action.h"
#include "../ApplicationManager.h"

class RedoAction : public Action
{
private:
public:

	RedoAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
};

