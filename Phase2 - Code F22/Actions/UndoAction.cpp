#include "UndoAction.h"
UndoAction::UndoAction(ApplicationManager* pApp) :Action(pApp)
{
}
//Reads parameters required for action to execute (code depends on action type)
void UndoAction::ReadActionParameters()
{
}

//Execute action (code depends on action type)
void UndoAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	pManager->UndoLastAction();
}
bool UndoAction::CanBeRecorded() const
{
	return true;
}
