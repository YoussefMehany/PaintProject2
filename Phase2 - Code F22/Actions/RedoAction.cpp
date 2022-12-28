#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void RedoAction::ReadActionParameters()
{
}

//Execute action (code depends on action type)
bool RedoAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	pManager->RedoLastAction();
	return false;
}
bool RedoAction::CanBeRecorded() const
{
	return true;
}
