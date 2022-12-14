#include "SwitchToPlayAction.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp) :Action(pApp)
{
	
}
//Reads parameters required for action to execute (code depends on action type)
void SwitchToPlayAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Play Mode");
	CFigure* SelectedFig = pManager->GetSelectedFig();
	if (SelectedFig) 
	{
		pManager->SetSelectedFig(NULL);
		SelectedFig->SetSelected(false);
	}
	pOut->CreatePlayToolBar();
	if (UI.Sound)
	{
		PlaySound(TEXT("Sound/Lets_Play.wav"), NULL, SND_SYNC);
	}
}

//Execute action (code depends on action type)
bool SwitchToPlayAction::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->SetPlayMode(true);
	pManager->SetRec(false);
	return true;
}
bool SwitchToPlayAction::CanBeRecorded() const
{
	return false;
}