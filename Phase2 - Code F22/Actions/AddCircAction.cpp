#include "AddCircAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircAction::AddCircAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	if (pManager->IsUndoAction())
	{
		P1 = P1_Undo;
	}
	else
	{
		//Read the center point
		pOut->PrintMessage("New Circle: Click at the Center");
		if (pManager->IsPlayingRec())
			P1 = P1_Rec;
		else {
			pIn->GetPointClicked(P1.x, P1.y);
			P1_Rec = P1;
			P1_Undo = P1;
		}
	}


	

	
	if (pManager->IsUndoAction())
	{
		P2 = P2_Undo;
	}
	else
	{
        //Read 2nd corner and store in point P2
        pOut->PrintMessage("New Circle: Click at a point on the radius");
		if (pManager->IsPlayingRec())
			P2 = P2_Rec;
		else {
			pIn->GetPointClicked(P2.x, P2.y);
			P2_Rec = P2;
			P2_Undo = P2;
		}
		pOut->ClearStatusBar();
	}


	CircGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	

}

//Execute the action
void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a Circle with the parameters read from the user
	CCircle* R = new CCircle(P1, P2, CircGfxInfo);

	//Add the Circle to the list of figures
	pManager->AddFigure(R);
}
