#include "StartRecAction.h"

StartRecAction::StartRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StartRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

}

//Execute action (code depends on action type)
void StartRecAction::Execute()
{
	ReadActionParameters();

}