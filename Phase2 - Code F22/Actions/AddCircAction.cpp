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

	pOut->PrintMessage("New Circle: Click at the Center");

	//Read the center point
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}

	pOut->PrintMessage("New Circle: Click at a point on the radius");

	//Read 2nd corner and store in point P2
	if (pManager->IsPlayingRec())
		P2 = P2_Rec;
	else {
		pIn->GetPointClicked(P2.x, P2.y);
		P2_Rec = P2;
	}

	CircGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CCircle* R = new CCircle(P1, P2, CircGfxInfo);

	//Add the rectangle to the list of figures
	pManager->SetLastAction(DRAW_CIRC);
	pManager->AddFigure(R);
}
