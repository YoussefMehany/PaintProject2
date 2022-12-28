#include "PlayRecAction.h"

PlayRecAction::PlayRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void PlayRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Play_recording.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Playing Recording");
}

//Execute action (code depends on action type)
void PlayRecAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	pManager->PlayRec();
}
bool PlayRecAction::CanBeRecorded() const
{
	return false;
}