#include "ChangeColorAction.h"

ChangeColorAction::ChangeColorAction(ApplicationManager* pApp, color clr) :Action(pApp)
{
	colour = clr;
	Saved = NULL;
	Saved_Redo = NULL;
}
//Reads parameters required for action to execute (code depends on action type)
void ChangeColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pManager->Add_Undo_Redo_Actions(this);
	Saved = pManager->GetSelectedFig()->GetNewFigure();

}

//Execute action (code depends on action type)
bool ChangeColorAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	CFigure* selected = pManager->GetSelectedFig();
	if (UI.Choose == BORDER)
	{
		UI.DrawColor = colour;
		selected->ChngDrawClr(UI.DrawColor);
	}
	else
	{
		UI.IsFilled = true;
		UI.FillColor = colour;
		selected->ChngFillClr(UI.FillColor);
	}
	Saved_Redo = selected->GetNewFigure();
	return false;
}
bool ChangeColorAction::CanBeRecorded() const
{
	return true;
}
void ChangeColorAction::UndoActions()
{
	pManager->SwapFigures(Saved);
	Saved->ChngClr();
	Saved = Saved->GetNewFigure();
}
void ChangeColorAction::RedoActions()
{
	pManager->SwapFigures(Saved_Redo);
	Saved_Redo->ChngClr();
	Saved_Redo = Saved_Redo->GetNewFigure();
}
ChangeColorAction::~ChangeColorAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
	if (Saved)
		delete Saved;
}