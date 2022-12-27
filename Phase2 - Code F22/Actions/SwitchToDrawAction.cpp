#include "SwitchToDrawAction.h"

SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void SwitchToDrawAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Back To Draw Mode");
	pOut->CreateDrawToolBar();
}

//Execute action (code depends on action type)
void SwitchToDrawAction::Execute()
{
	ReadActionParameters();
	pManager->SetPlayMode(false);
}