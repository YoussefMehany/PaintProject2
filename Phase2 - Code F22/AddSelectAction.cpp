#include "AddSelectAction.h"

AddSelectAction::AddSelectAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void AddSelectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Position : Click on any figure");
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void AddSelectAction::Execute()
{
	ReadActionParameters();

	pManager->SelectFigure(P);
}