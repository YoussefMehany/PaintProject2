#include "UndoAction.h"
UndoAction::UndoAction(ApplicationManager* pApp) :Action(pApp)
{
}
//Reads parameters required for action to execute (code depends on action type)
void UndoAction::ReadActionParameters()
{
}

//Execute action (code depends on action type)
bool UndoAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetUndoRedoLimit() == 5 && pManager->IsUndo())
	{
		pOut->PrintMessage("Undo Limit Exceeded,Please make another action first");
		return true;
	}
	if (pManager->GetUndoRedoCount() == 0)
	{
		pOut->PrintMessage("No Action to undo");
		return true;
	}
	pManager->UndoLastAction();
	if (pManager->IsRecording())
	{
		return false;
	}
	return true;
}
bool UndoAction::CanBeRecorded() const
{
	return true;
}