#include "StartRecAction.h"

StartRecAction::StartRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StartRecAction::ReadActionParameters()
{

}

//Execute action (code depends on action type)
void StartRecAction::Execute()
{
	ReadActionParameters();
	pManager->SetRec(true);
}