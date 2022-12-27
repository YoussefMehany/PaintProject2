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


	//Read 1st corner and store in point P1
	pOut->PrintMessage("New Rectangle: Click at first corner");
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}


	//Read 2nd corner and store in point P2
	pOut->PrintMessage("New Rectangle: Click at second corner");
	if (pManager->IsPlayingRec())
		P2 = P2_Rec;
	else {
		pIn->GetPointClicked(P2.x, P2.y);
		P2_Rec = P2;
	}
	pOut->ClearStatusBar();


	RectGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();



}

//Execute the action
void AddRectAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	//Create a rectangle with the parameters read from the user
	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
}
void AddRectAction::UndoActions()
{
	Saved_Redo = new CRectangle(P1, P2, RectGfxInfo);
	Saved_Redo->SetID(id);
	pManager->DeleteLastFig();

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