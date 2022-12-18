#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{

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
	pManager->SetLastAction(DELETE_FIGURE);
}