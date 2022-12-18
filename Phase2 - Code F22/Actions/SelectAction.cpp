#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void SelectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Position : Click on any figure");
	if (pManager->IsPlayingRec())
		P = P_Rec;
	else {
		pIn->GetPointClicked(P.x, P.y);
		P_Rec = P;
	}
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void SelectAction::Execute()
{
	ReadActionParameters();

	pManager->SelectFigure(P);
}