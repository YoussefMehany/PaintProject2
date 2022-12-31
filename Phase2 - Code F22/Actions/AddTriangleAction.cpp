#pragma once
#include "AddTriangleAction.h"
#include "../Figures/CTriangle.h"
AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Triangle.wav"), NULL, SND_SYNC);
	}
	//Read 1st corner and store in point P1
	pOut->PrintMessage("New Triangle: Click at first corner");
	pIn->GetPointClicked(P1.x, P1.y);

	//Read 2nd corner and store in point P2
	pOut->PrintMessage("New Triangle: Click at second corner");
	pIn->GetPointClicked(P2.x, P2.y);


	//Read 3rd corner and store in point P2
	pOut->PrintMessage("New Triangle: Click at third corner");
	pIn->GetPointClicked(P3.x, P3.y);

	pOut->ClearStatusBar();

	TriangleGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();



}

//Execute the action
bool AddTriangleAction::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->Add_Undo_Redo_Actions(this);

	//Create a Triangle with the parameters read from the user

	CTriangle* R = new CTriangle(P1, P2, P3, TriangleGfxInfo);

	//Add the Triangle to the list of figures

	Saved_Redo = R->GetNewFigure();

	pManager->AddFigure(R);

	return false;
}
bool AddTriangleAction::CanBeRecorded() const
{
	return true;
}
void AddTriangleAction::UndoActions()
{	
	pManager->DeleteFigure(pManager->GetLastAdd());
}
void AddTriangleAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
void AddTriangleAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;
	Saved_Redo = NULL;
}
AddTriangleAction::~AddTriangleAction()
{
	ClearSaved();
}