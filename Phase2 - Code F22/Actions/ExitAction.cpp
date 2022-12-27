#include "ExitAction.h"

ExitAction::ExitAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ExitAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void ExitAction::Execute()
{
	ReadActionParameters();

	pManager->ClearAll();
}