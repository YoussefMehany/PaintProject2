#include "SwitchToPlayAction.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp) :Action(pApp)
{
	
}
//Reads parameters required for action to execute (code depends on action type)
void SwitchToPlayAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Play Mode");
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
void SwitchToPlayAction::Execute()
{
	ReadActionParameters();
	pManager->SetPlayMode(true);
}