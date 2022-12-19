#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void RedoAction::ReadActionParameters()
{
}

//Execute action (code depends on action type)
void RedoAction::Execute()
{
	ReadActionParameters();
	pManager->RedoLastAction();
}
