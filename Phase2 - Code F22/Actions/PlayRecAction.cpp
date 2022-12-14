#include "PlayRecAction.h"

PlayRecAction::PlayRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void PlayRecAction::ReadActionParameters()
{
	
}

//Execute action (code depends on action type)
bool PlayRecAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	if (pManager->IsRecording()) 
	{
		pOut->PrintMessage("Stop the recording first");
		return true;
	}
	if (pManager->GetRecCount() == 0)
	{
		pOut->PrintMessage("Record some actions first");
		return true;
	}
	if (UI.Sound)
	{
		PlaySound(TEXT("Sound/Play_recording.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Playing Recording");
	pManager->SetPlayingRec(true);
	pManager->ClearAll();
	pManager->PlayRec();
	pManager->SetPlayingRec(false);
	return true;
}
bool PlayRecAction::CanBeRecorded() const
{
	return false;
}