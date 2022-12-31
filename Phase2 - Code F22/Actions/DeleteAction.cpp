#include "DeleteAction.h"
DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved = NULL;
}
//Reads parameters required for action to execute (code depends on action type)
void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	if (pManager->IsSoundOn())
	{
		PlaySound(TEXT("Sound/Deleted.wav"), NULL, SND_SYNC);
	}
}

//Execute action (code depends on action type)
bool DeleteAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	if (ReadParams)
	{
		if (pManager->GetSelectedFig() == NULL)
		{
			pOut->PrintMessage("Please Select a Figure First");
			return true;
		}
		ReadActionParameters();
	}

	pManager->Add_Undo_Redo_Actions(this);

	Saved = pManager->GetSelectedFig()->GetNewFigure();

	Saved->SetSelected(false);

	pManager->DeleteFigure();
	return false;
}
void DeleteAction::UndoActions()
{
	pManager->AddFigure(Saved);
	Saved = Saved->GetNewFigure();
}
void DeleteAction::RedoActions()
{
	pManager->DeleteFigure(Saved);
}
bool DeleteAction::CanBeRecorded() const
{
	return true;
}
void DeleteAction::ClearSaved()
{
	if (Saved)
		delete Saved;
	Saved = NULL;
}
DeleteAction::~DeleteAction()
{
	ClearSaved();
}