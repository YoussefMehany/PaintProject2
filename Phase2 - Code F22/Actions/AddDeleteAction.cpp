#include "AddDeleteAction.h"

AddDeleteAction::AddDeleteAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void AddDeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void AddDeleteAction::Execute()
{
	ReadActionParameters();

	pManager->DeleteFigure();
}