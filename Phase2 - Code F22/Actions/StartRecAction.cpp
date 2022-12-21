#include "StartRecAction.h"

StartRecAction::StartRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StartRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Recording Started");
}

//Execute action (code depends on action type)
void StartRecAction::Execute()
{
	ReadActionParameters();
	pManager->SetRec(true);
}