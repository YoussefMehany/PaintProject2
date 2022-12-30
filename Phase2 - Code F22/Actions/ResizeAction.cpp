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
	pManager->Add_Undo_Redo_Actions(this);
	Saved = pManager->GetSelectedFig()->GetNewFigure();
	CFigure* Fig = pManager->GetSelectedFig();

	bool Check_1 = false;
	while (pIn->GetMouseState(P.x, P.y) == BUTTON_UP)
	{
		//Sleep(10);
		while (pIn->GetMouseState(P.x, P.y) == BUTTON_DOWN)
		{
			Sleep(20);
			if (!Fig->Resize(P))
			{
				pOut->PrintMessage("Please resize the Selected figure ,Try again");
				Check_1 = true;
				return true;
			}
			pManager->UpdateInterface();
			Check_1 = true;
		}
		if (Check_1)
		{
			Saved = pManager->GetSelectedFig()->GetNewFigure();
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
ResizeAction::~ResizeAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
}