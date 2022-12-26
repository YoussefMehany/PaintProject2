#include "MoveAction.h"
#include <iostream>
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
		//pIn->GetPointClicked(P.x, P.y);
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
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	bool Check_1 = false;
	bool Check_2 = true;
	while (pIn->GetMouseState(P.x, P.y) == BUTTON_UP) {
		while (pIn->GetMouseState(P.x, P.y) == BUTTON_DOWN)
		{
			Sleep(5);
			if (pManager->GetFigure(P) != pManager->GetSelectedFig()&& Check_2 ) { Check_1 = true; break; }
			pManager->MoveFigure(P);
			pManager->UpdateInterface();
			Check_1 = true;
			Check_2 = false;
		}
		if (Check_1)  break;
	}
	Saved_Redo = pManager->GetSelectedFig()->GetNewFigure();

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