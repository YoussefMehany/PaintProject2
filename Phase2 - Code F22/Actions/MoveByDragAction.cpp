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
	if (UI.Sound)
	{
		PlaySound(TEXT("Sound/Move_by_drag.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Drag the selected figure");
}

//Execute action (code depends on action type)
bool MoveByDragAction::Execute(bool ReadParams)
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

	Input* pIn = pManager->GetInput();
	CFigure* Fig = pManager->GetSelectedFig();
	bool Check_1 = false;
	bool Check_2 = true;
	Saved = Fig->GetNewFigure();
	if(!pManager->IsPlayingRec())
	{
		while (pIn->GetMouseState(P.x, P.y) == BUTTON_UP)
		{
			Sleep(10);
			while (pIn->GetMouseState(P.x, P.y) == BUTTON_DOWN)
			{
				Sleep(20);
				if (pManager->GetFigure(P) != Fig && Check_2)
				{
					pOut->PrintMessage("Please drag the Selected figure ,Try again");
					return true;
				}
				Fig->MoveTo(P);
				pManager->UpdateInterface();
				Check_1 = true;
				Check_2 = false;
			}
			if (Check_1)
			{
				break;
			}
		}
		P_Rec = P;
	}
	pManager->Add_Undo_Redo_Actions(this);
	if (pManager->IsPlayingRec())
	{
		P = P_Rec;
		Fig->MoveTo(P);
	}
	Saved_Redo = pManager->GetSelectedFig()->GetNewFigure();
	return false;
}
void MoveByDragAction::UndoActions()
{
	pManager->SwapFigures(Saved);
	Saved = Saved->GetNewFigure();
}
bool MoveByDragAction::CanBeRecorded() const
{
	return true;
}
void MoveByDragAction::RedoActions()
{
	pManager->SwapFigures(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
void MoveByDragAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
	Saved_Redo = NULL;
	Saved = NULL;
}
MoveByDragAction::~MoveByDragAction()
{
	ClearSaved();
}