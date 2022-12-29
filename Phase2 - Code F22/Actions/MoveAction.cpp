#include "MoveAction.h"

MoveAction::MoveAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved = NULL;
	Saved_Redo = NULL;
}
//Reads parameters required for action to execute (code depends on action type)
void MoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Move.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("New Position : Click at the new position");
	pIn->GetPointClicked(P.x, P.y);

	pOut->ClearStatusBar();
	pManager->Add_Undo_Redo_Actions(this);

	Saved = pManager->GetSelectedFig()->GetNewFigure();
}

//Execute action (code depends on action type)
bool MoveAction::Execute(bool ReadParams)
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

	CFigure* Fig = pManager->GetSelectedFig();
	Fig->MoveTo(P);
	Saved_Redo = pManager->GetSelectedFig()->GetNewFigure();
	return false;
}
void MoveAction::UndoActions()
{
	pManager->SwapFigures(Saved);
	Saved = Saved->GetNewFigure();
}
void MoveAction::RedoActions()
{
	pManager->SwapFigures(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
bool MoveAction::CanBeRecorded() const
{
	return true;
}
MoveAction::~MoveAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
}