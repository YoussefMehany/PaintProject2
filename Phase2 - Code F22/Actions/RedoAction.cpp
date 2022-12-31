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
	Output* pOut = pManager->GetOutput();
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	if ((!pManager->IsUndo() && !pManager->IsRedo()) || pManager->GetUndoRedoLimit() == 0)
	{
		pOut->PrintMessage("No Undo to Redo");
		return true;
	}
	pManager->RedoLastAction();
	return false;
}
bool RedoAction::CanBeRecorded() const
{
	return true;
}
bool RedoAction::CanBeDeleted() const
{
	return true;
}
