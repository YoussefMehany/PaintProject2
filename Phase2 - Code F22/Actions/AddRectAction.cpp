#include "AddRectAction.h"

AddRectAction::AddRectAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
}

void AddRectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	

	if (pManager->IsSoundOn()) 
	{
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
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->Add_Undo_Redo_Actions(this);

	//Create a rectangle with the parameters read from the user

	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);

	//Add the rectangle to the list of figures

	Saved_Redo = R->GetNewFigure();

	pManager->AddFigure(R);

	return false;
}
void AddRectAction::UndoActions()
{	
	pManager->DeleteFigure(pManager->GetLastAdd());
}
void AddRectAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
bool AddRectAction::CanBeRecorded() const
{
	return true;
}
void AddRectAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;
	Saved_Redo = NULL;
}
AddRectAction::~AddRectAction()
{
	ClearSaved();
}