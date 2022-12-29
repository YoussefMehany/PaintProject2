#include "AddTriangleAction.h"
#include "..\Figures\CTriangle.h"
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
	//Create a Triangle with the parameters read from the user
	CTriangle* R = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
	return false;
}
bool AddTriangleAction::CanBeRecorded() const
{
	return true;
}
void AddTriangleAction::UndoActions()
{
	Saved_Redo = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	Saved_Redo->SetID(id);
	if (pManager->GetSelectedFig() != NULL)
		if (pManager->GetSelectedFig()->GetID() == id) 
		{
			Saved_Redo->SetSelected(true); 
		}
	pManager->DeleteFigure();
}
void AddTriangleAction::RedoActions()
{
	if (Saved_Redo->IsSelected()) 
	{
		pManager->SetSelectedFig(Saved_Redo); 
	}
	pManager->AddFigure(Saved_Redo);
}
AddTriangleAction::~AddTriangleAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
}