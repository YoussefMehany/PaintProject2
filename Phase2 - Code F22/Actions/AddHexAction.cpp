#include "AddHexAction.h"

AddHexAction::AddHexAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
}

void AddHexAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Hexagon.wav"), NULL, SND_SYNC);
	}
	//Read the center point
	pOut->PrintMessage("New Hexagon: Click at the Center");
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->ClearStatusBar();


	HexGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexGfxInfo.FillClr = pOut->getCrntFillColor();



}

//Execute the action
bool AddHexAction::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pManager->Add_Undo_Redo_Actions(this);

	//Create a hexagon with the parameters read from the user

	CHexagon* R = new CHexagon(P1, HexGfxInfo);

	//Add the hexagon to the list of figure

	Saved_Redo = R->GetNewFigure();
	pManager->AddFigure(R);
	
	return false;
}
void AddHexAction::UndoActions()
{
	pManager->DeleteFigure(pManager->GetLastAdd());
}
void AddHexAction::RedoActions()
{
	pManager->AddFigure(Saved_Redo);
	Saved_Redo = Saved_Redo->GetNewFigure();
}
bool AddHexAction::CanBeRecorded() const
{
	return true;
}
void AddHexAction::ClearSaved()
{
	if (Saved_Redo)
		delete Saved_Redo;
	Saved_Redo = NULL;
}
AddHexAction::~AddHexAction()
{
	ClearSaved();
}