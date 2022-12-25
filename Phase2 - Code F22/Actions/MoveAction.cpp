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
		pOut->PrintMessage("New Position : Click at the new position");
		if (pManager->IsPlayingRec())
			P = P_Rec;
		else {
			pIn->GetPointClicked(P.x, P.y);
			P_Rec = P;
		}
      pOut->ClearStatusBar();
	  pManager->Add_Undo_Redo_Actions(this);

	  Saved = pManager->GetSelectedFig()->GetNewFigure();
}

//Execute action (code depends on action type)
void MoveAction::Execute()
{
	ReadActionParameters();
	pManager->MoveFigure(P);
	Saved_Redo= pManager->GetSelectedFig()->GetNewFigure();
	
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
MoveAction::~MoveAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
}