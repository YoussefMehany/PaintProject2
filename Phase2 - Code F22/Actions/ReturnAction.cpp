#include "ReturnAction.h"

ReturnAction::ReturnAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ReturnAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateDrawToolBar();
}

//Execute action (code depends on action type)
void ReturnAction::Execute()
{
	ReadActionParameters();
}