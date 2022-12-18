#include "ChangeColorAction.h"

ChangeColorAction::ChangeColorAction(ApplicationManager* pApp, color clr) :Action(pApp)
{
	colour = clr;
}
//Reads parameters required for action to execute (code depends on action type)
void ChangeColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void ChangeColorAction::Execute()
{
	ReadActionParameters();
	pManager->ChangeColor(colour);
}