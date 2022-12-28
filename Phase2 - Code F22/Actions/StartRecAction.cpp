#include "StartRecAction.h"

StartRecAction::StartRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StartRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (!pManager->IsRecording()) {
		if (pManager->IsSoundOn()) {
			PlaySound(TEXT("Sound/Recording_Started.wav"), NULL, SND_SYNC);
		}
		pOut->PrintMessage("Recording Started");
	}
}

//Execute action (code depends on action type)
bool StartRecAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	if (pManager->IsRecording()) {
		Action* RecAction = pManager->GetLastAction();
		if (RecAction->CanBeRecorded()) {
			pManager->AddActionRec(RecAction);
		}
	}
	pManager->SetRec(true);
	return false;
}
bool StartRecAction::CanBeRecorded() const
{
	return false;
}