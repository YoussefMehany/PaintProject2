#include "AddTriangleAction.h"
#include "..\Figures\CTriangle.h"
//#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
	id = 0;
}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pManager->Add_Undo_Redo_Actions(this);

	//Read 1st corner and store in point P1
	pOut->PrintMessage("New Triangle: Click at first corner");
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}
	//Read 2nd corner and store in point P2
	pOut->PrintMessage("New Triangle: Click at second corner");
	if (pManager->IsPlayingRec())
		P2 = P2_Rec;
	else {
		pIn->GetPointClicked(P2.x, P2.y);
		P2_Rec = P2;
	}

	//Read 3rd corner and store in point P2
	pOut->PrintMessage("New Triangle: Click at third corner");
	if (pManager->IsPlayingRec())
		P3 = P3_Rec;
	else {
		pIn->GetPointClicked(P3.x, P3.y);
		P3_Rec = P3;
	}
	pOut->ClearStatusBar();

	TriangleGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();



}

//Execute the action
void AddTriangleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	//Create a Triangle with the parameters read from the user
	CTriangle* R = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
}
void AddTriangleAction::UndoActions()
{
	Saved_Redo = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	Saved_Redo->SetID(id);
	pManager->DeleteLastFig();
}
void AddTriangleAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
}
AddTriangleAction::~AddTriangleAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
}