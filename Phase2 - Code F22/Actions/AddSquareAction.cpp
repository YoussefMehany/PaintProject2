#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddSquareAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click at the Center");

	//Read 1st corner and store in point P1
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}

	SquareGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddSquareAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CSquare* R = new CSquare(P1, SquareGfxInfo);

	//Add the rectangle to the list of figures
	pManager->SetLastAction(DRAW_SQUARE);
	pManager->AddFigure(R);
}
