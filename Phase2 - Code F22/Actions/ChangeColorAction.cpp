#include "ChangeColorAction.h"

ChangeColorAction::ChangeColorAction(ApplicationManager* pApp, color clr) :Action(pApp)
{
	colour = clr;
	Saved= pManager->GetSelectedFig()->GetNewFigure();
}
//Reads parameters required for action to execute (code depends on action type)
void ChangeColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void ChangeColorAction::Execute()
{
	ReadActionParameters();
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
}
void ChangeColorAction::UndoActions()
{
	pManager->SwapFigures(Saved);
	Saved = Saved->GetNewFigure();
}
void ChangeColorAction::RedoActions()
{
	pManager->SwapFigures(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}