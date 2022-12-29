#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved = NULL;
	Saved_Redo = NULL;
}
//Reads parameters required for action to execute (code depends on action type)
void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pManager->Add_Undo_Redo_Actions(this);
	Saved = pManager->GetSelectedFig()->GetNewFigure();
	Saved_Redo = pManager->GetSelectedFig()->GetNewFigure();
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
	Saved->SetSelected(false);
	Saved_Redo->SetSelected(false);
	pManager->DeleteFigure();
	return false;
}
void DeleteAction::UndoActions()
{
	if (Saved->IsSelected()) 
	{
		pManager->GetSelectedFig()->SetSelected(false);
		pManager->SetSelectedFig(Saved);
	}
	pManager->AddFigure(Saved);
	Saved = Saved->GetNewFigure();
}
void DeleteAction::RedoActions()
{
	pManager->DeleteFigure(Saved_Redo);
}
bool DeleteAction::CanBeRecorded() const
{
	return true;
}
DeleteAction::~DeleteAction()
{
	if (Saved)
		delete Saved;
}