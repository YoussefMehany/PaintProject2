#include "Action.h"
#include "../ApplicationManager.h"
class SelectAction :public Action
{
private:
	Point P;
	Point P_Rec;
public:
	SelectAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute(bool ReadParams = true);
	virtual bool CanBeRecorded() const;
};

