#include "StopRecAction.h"

StopRecAction::StopRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StopRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Recording Stopped");
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Recording_Stopped.wav"), NULL, SND_SYNC);
	}

}

//Execute action (code depends on action type)
bool StopRecAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->SetRec(false);
	return true;
}
bool StopRecAction::CanBeRecorded() const
{
	return false;
}