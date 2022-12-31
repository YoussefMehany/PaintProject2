#include "ResizeAction.h"

ResizeAction::ResizeAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved = NULL;
	Saved_Redo = NULL;
}
//Reads parameters required for action to execute (code depends on action type)
void ResizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	
	if (pManager->IsSoundOn())
	{
		PlaySound(TEXT("Sound/Move.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Resize the selected fig");
}

//Execute action (code depends on action type)

bool ResizeAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (ReadParams)
	{

		if (pManager->GetSelectedFig() == NULL)
		{
			pOut->PrintMessage("Please Select a Figure First");
			return true;
		}
		ReadActionParameters();
	}
	Saved = pManager->GetSelectedFig()->GetNewFigure();
	CFigure* Fig = pManager->GetSelectedFig();

	bool Check_1 = false;
	bool Check_2 = true;
	if(!pManager->IsPlayingRec())
	{
		while (pIn->GetMouseState(P.x, P.y) == BUTTON_UP)
		{
			Sleep(10);
			while (pIn->GetMouseState(P.x, P.y) == BUTTON_DOWN)
			{
				Sleep(20);
				if ((pManager->GetFigure(P) != Fig || !Fig->IsCorner(P)) && Check_2)
				{
					pOut->PrintMessage("Please drag a corner of the selected figure, Try again");
					return true;
				}
				Fig->Resize(P);
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
		Fig->Resize(P);
	}
	Saved_Redo = Fig->GetNewFigure();
	return false;
}
void ResizeAction::UndoActions()
{
	pManager->SwapFigures(Saved);
	Saved = Saved->GetNewFigure();
}
void ResizeAction::RedoActions()
{
	pManager->SwapFigures(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
bool ResizeAction::CanBeRecorded() const
{
	return true;
}
void ResizeAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
	Saved_Redo = NULL;
	Saved = NULL;
}
ResizeAction::~ResizeAction()
{
	ClearSaved();
}