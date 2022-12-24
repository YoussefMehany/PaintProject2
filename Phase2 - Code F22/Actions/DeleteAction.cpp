#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved = pManager->GetSelectedFig()->GetNewFigure();
	Saved->SetSelected(false);
	Saved_Redo = Saved->GetNewFigure();
}
//Reads parameters required for action to execute (code depends on action type)
void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void DeleteAction::Execute()
{
	ReadActionParameters();
	pManager->DeleteFigure();
}
void DeleteAction::UndoActions()
{
	pManager->AddFigure(Saved);
	Saved=Saved->GetNewFigure();
}
void DeleteAction::RedoActions()
{
	CFigure*S= Saved_Redo->GetNewFigure();
	pManager->DeleteFigure(Saved_Redo);
	Saved_Redo = S;
}