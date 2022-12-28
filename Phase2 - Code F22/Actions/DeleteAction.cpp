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
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Deleted.wav"), NULL, SND_SYNC);
	}
	pOut->ClearStatusBar();
	pManager->Add_Undo_Redo_Actions(this);
	Saved = pManager->GetSelectedFig()->GetNewFigure();
	Saved->SetSelected(false);
}

//Execute action (code depends on action type)
bool DeleteAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	pManager->DeleteFigure();
	return false;
}
void DeleteAction::UndoActions()
{
	pManager->AddFigure(Saved);
	Saved=Saved->GetNewFigure();
}
void DeleteAction::RedoActions()
{
	pManager->DeleteFigure(true);
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