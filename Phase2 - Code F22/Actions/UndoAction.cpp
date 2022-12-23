#include "UndoAction.h"
#include <iostream>
UndoAction::UndoAction(ApplicationManager* pApp) :Action(pApp)
{
}
//Reads parameters required for action to execute (code depends on action type)
void UndoAction::ReadActionParameters()
{
}

//Execute action (code depends on action type)
void UndoAction::Execute()
{
	ReadActionParameters();
	pManager->UndoLastAction();
}
