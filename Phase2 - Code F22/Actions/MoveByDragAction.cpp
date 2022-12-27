#include "MoveByDragAction.h"

MoveByDragAction::MoveByDragAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved = NULL;
	Saved_Redo = NULL;
}
//Reads parameters required for action to execute (code depends on action type)
void MoveByDragAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Drag the selected figure");

	Saved = pManager->GetSelectedFig()->GetNewFigure();
}

//Execute action (code depends on action type)
void MoveByDragAction::Execute()
{
	ReadActionParameters();

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	bool Check_1 = false;
	bool Check_2 = true;
	while (pIn->GetMouseState(P.x, P.y) == BUTTON_UP) {
		while (pIn->GetMouseState(P.x, P.y) == BUTTON_DOWN)
		{
			Sleep(20);
			if (pManager->GetFigure(P) != pManager->GetSelectedFig() && Check_2)
			{
				pOut->PrintMessage("Please drag the Selected figure ,Try agian");
				Check_1 = true;
				break;
			}
			pManager->MoveFigure(P);
			pManager->UpdateInterface();
			Check_1 = true;
			Check_2 = false;
		}
		if (Check_1)
		{
			pManager->Add_Undo_Redo_Actions(this);
			break;
		}
	}
	if (pManager->IsPlayingRec())
		P = P_Rec;
	else {
		P_Rec = P;
	}
	Saved_Redo = pManager->GetSelectedFig()->GetNewFigure();
	//pOut->PrintMessage("out");
}
void MoveByDragAction::UndoActions()
{
	pManager->SwapFigures(Saved);
	Saved = Saved->GetNewFigure();
}
void MoveByDragAction::RedoActions()
{
	pManager->SwapFigures(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
MoveByDragAction::~MoveByDragAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
}