#include "AddRectAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
	id = 0;
}

void AddRectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pManager->Add_Undo_Redo_Actions(this);

	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Rectangle.wav"), NULL, SND_SYNC);
	}
	//Read 1st corner and store in point P1
	pOut->PrintMessage("New Rectangle: Click at first corner");
	pIn->GetPointClicked(P1.x, P1.y);


	//Read 2nd corner and store in point P2
	pOut->PrintMessage("New Rectangle: Click at second corner");
	pIn->GetPointClicked(P2.x, P2.y);
	pOut->ClearStatusBar();


	RectGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();



}

//Execute the action
bool AddRectAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	//Create a rectangle with the parameters read from the user
	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
	return false;
}
void AddRectAction::UndoActions()
{
	Saved_Redo = new CRectangle(P1, P2, RectGfxInfo);
	Saved_Redo->SetID(id);
	pManager->DeleteFigure(true);

}
bool AddRectAction::CanBeRecorded() const
{
	return true;
}
void AddRectAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
}
AddRectAction::~AddRectAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
}