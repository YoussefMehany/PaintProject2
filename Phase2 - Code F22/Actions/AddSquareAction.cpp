#include "AddSquareAction.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
}

void AddSquareAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (UI.Sound)
	{
		PlaySound(TEXT("Sound/Square.wav"), NULL, SND_SYNC);
	}
	//Read 1st corner and store in point P1
	pOut->PrintMessage("New Square: Click at the Center");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->ClearStatusBar();

	SquareGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();


}

//Execute the action
bool AddSquareAction::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->Add_Undo_Redo_Actions(this);

	//Create a square with the parameters read from the user

	CSquare* R = new CSquare(P1, SquareGfxInfo);

	//Add the square to the list of figures

	Saved_Redo = R->GetNewFigure();

	pManager->AddFigure(R);

	return false;
}
bool AddSquareAction::CanBeRecorded() const
{
	return true;
}
void AddSquareAction::UndoActions()
{	
	pManager->DeleteFigure(pManager->GetLastAdd());
}
void AddSquareAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
void AddSquareAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;
	Saved_Redo = NULL;
}
AddSquareAction::~AddSquareAction()
{
	ClearSaved();
}