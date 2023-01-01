#include "StartRecAction.h"

StartRecAction::StartRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void StartRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	if (UI.Sound)
	{
		PlaySound(TEXT("Sound/Recording_Started.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Recording Started");

}

//Execute action (code depends on action type)
bool StartRecAction::Execute(bool ReadParams)
{
	if (ReadParams)
	{
		Output* pOut = pManager->GetOutput();
		if (pManager->GetFigCount() != 0 || pManager->GetUndoRedoCount() != 0 || pManager->GetRecCount() != 0)
		{
			pOut->PrintMessage("You can only record after the program start or after clear all");
			return true;
		}
		ReadActionParameters();
	}
	if (pManager->IsRecording())
	{
		Action* RecAction = pManager->GetLastAction();
		if (RecAction->CanBeRecorded())
		{
			pManager->AddActionRec(RecAction);
		}
		else if (RecAction != this)
		{
			pManager->SetRec(false);
			return true;
		}
	}
	pManager->SetRec(true);
	if (pManager->IsRecording())
	{
		return false;
	}
	return true;
}
bool StartRecAction::CanBeRecorded() const
{
	return false;
}