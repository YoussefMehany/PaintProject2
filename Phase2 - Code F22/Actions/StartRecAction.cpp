#include "StartRecAction.h"

StartRecAction::StartRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StartRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Recording_Started.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Recording Started");
}

//Execute action (code depends on action type)
void StartRecAction::Execute()
{
	ReadActionParameters();
	pManager->SetRec(true);
}