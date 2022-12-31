#include "ClearAllAction.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ClearAllAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
bool ClearAllAction::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->ClearAll();
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Cleared.wav"), NULL, SND_SYNC);
	}
	if (pManager->IsRecording())
	{
		return false;
	}
	return true;
}
bool ClearAllAction::CanBeRecorded() const
{
	return true;
}