#include "AddCircAction.h"
AddCircAction::AddCircAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
}

void AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	if (UI.Sound)
	{
		PlaySound(TEXT("Sound/Circle.wav"), NULL, SND_SYNC);
	}
	//Read the center point
	pOut->PrintMessage("New Circle: Click at the Center");
	pIn->GetPointClicked(P1.x, P1.y);


	//Read 2nd corner and store in point P2
	pOut->PrintMessage("New Circle: Click at a point on the radius");
	pIn->GetPointClicked(P2.x, P2.y);

	pOut->ClearStatusBar();
	CircGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();
}

//Execute the action
bool AddCircAction::Execute(bool ReadParams)
{
	if (ReadParams)
	{
		ReadActionParameters();
	}
	pManager->Add_Undo_Redo_Actions(this);

	//Create a Circle with the parameters read from the user

	CCircle* R = new CCircle(P1, P2, CircGfxInfo);

	//Add the Circle to the list of figures

	Saved_Redo = R->GetNewFigure();

	pManager->AddFigure(R);
	return false;
}
void AddCircAction::UndoActions()
{
	pManager->DeleteFigure(pManager->GetLastAdd());
}
void AddCircAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
bool AddCircAction::CanBeRecorded() const
{
	return true;
}
void AddCircAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;

	Saved_Redo = NULL;
}
AddCircAction::~AddCircAction()
{
	ClearSaved();
}