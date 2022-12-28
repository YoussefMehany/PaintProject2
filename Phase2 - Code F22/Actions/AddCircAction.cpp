#include "AddCircAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircAction::AddCircAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
	id = 0;
}

void AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pManager->Add_Undo_Redo_Actions(this);
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Circle.wav"), NULL, SND_SYNC);
	}
	//Read the center point
	pOut->PrintMessage("New Circle: Click at the Center");
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}

	//Read 2nd corner and store in point P2
	pOut->PrintMessage("New Circle: Click at a point on the radius");
	if (pManager->IsPlayingRec())
		P2 = P2_Rec;
	else {
		pIn->GetPointClicked(P2.x, P2.y);
		P2_Rec = P2;
	}

	pOut->ClearStatusBar();
	CircGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();
}

//Execute the action
void AddCircAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	//Create a Circle with the parameters read from the user
	CCircle* R = new CCircle(P1, P2, CircGfxInfo);

	//Add the Circle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();

}
void AddCircAction::UndoActions()
{
	Saved_Redo = new CCircle(P1, P2, CircGfxInfo);
	Saved_Redo->SetID(id);
	pManager->DeleteLastFig();
}
void AddCircAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
}
bool AddCircAction::CanBeRecorded() const
{
	return true;
}
AddCircAction::~AddCircAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
}