#include "AddMoveAction.h"

AddMoveAction::AddMoveAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void AddMoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Position : Click at the new position");
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void AddMoveAction::Execute()
{
	ReadActionParameters();
	
	pManager->MoveFigure(P);
}