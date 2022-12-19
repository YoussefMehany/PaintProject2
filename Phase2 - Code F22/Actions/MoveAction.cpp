#include "MoveAction.h"

MoveAction::MoveAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void MoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	if (pManager->IsUndoAction())
	{
		P = P_Undo;
	}
	else
	{
		pOut->PrintMessage("New Position : Click at the new position");
		if (pManager->IsPlayingRec())
			P = P_Rec;
		else {
			pIn->GetPointClicked(P.x, P.y);
			P_Rec = P;
			P_Undo = P;
		}
      pOut->ClearStatusBar();
	}

	
}

//Execute action (code depends on action type)
void MoveAction::Execute()
{
	ReadActionParameters();
	pManager->MoveFigure(P);
}