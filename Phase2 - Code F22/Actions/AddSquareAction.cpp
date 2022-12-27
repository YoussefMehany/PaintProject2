#include "AddSquareAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
	id = 0;
}

void AddSquareAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pManager->Add_Undo_Redo_Actions(this);

	//Read 1st corner and store in point P1
	pOut->PrintMessage("New Square: Click at the Center");
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}
	pOut->ClearStatusBar();

	SquareGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();


}

//Execute the action
void AddSquareAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	//Create a rectangle with the parameters read from the user
	CSquare* R = new CSquare(P1, SquareGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
}
void AddSquareAction::UndoActions()
{
	
	Saved_Redo = new CSquare(P1, SquareGfxInfo);
	Saved_Redo->SetID(id);
	pManager->DeleteLastFig();
}
void AddSquareAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
}
AddSquareAction::~AddSquareAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
}