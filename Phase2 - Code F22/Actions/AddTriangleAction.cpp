#include "AddTriangleAction.h"
#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first corner");

	//Read 1st corner and store in point P1
	if (pManager->IsRecording())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}

	pOut->PrintMessage("New Triangle: Click at second corner");

	//Read 2nd corner and store in point P2
	if (pManager->IsRecording())
		P2 = P2_Rec;
	else {
		pIn->GetPointClicked(P2.x, P2.y);
		P2_Rec = P2;
	}

	pOut->PrintMessage("New Triangle: Click at third corner");

	//Read 3rd corner and store in point P2
	if (pManager->IsRecording())
		P3 = P3_Rec;
	else {
		pIn->GetPointClicked(P3.x, P3.y);
		P3_Rec = P3;
	}

	TriangleGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriangleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a Triangle with the parameters read from the user
	CTriangle* R = new CTriangle(P1, P2, P3, TriangleGfxInfo);

	//Add the rectangle to the list of figures
	pManager->SetLastAction(DRAW_TRIANGLE);
	pManager->AddFigure(R);
}
