#include "StopRecAction.h"

StopRecAction::StopRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StopRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Recording Stopped");
}

//Execute action (code depends on action type)
void StopRecAction::Execute()
{
	ReadActionParameters();
	pManager->SetRec(false);
}