#include "AddHexAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddHexAction::AddHexAction(ApplicationManager* pApp) :Action(pApp)
{
	Saved_Redo = NULL;
	id = 0;
}

void AddHexAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pManager->Add_Undo_Redo_Actions(this);
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
	//Create a rectangle with the parameters read from the user
	CHexagon* R = new CHexagon(P1, HexGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
	return false;
}
void AddHexAction::UndoActions()
{
	Saved_Redo = new CHexagon(P1, HexGfxInfo);
	Saved_Redo->SetID(id);
	if (pManager->GetSelectedFig() != NULL)
		if (pManager->GetSelectedFig()->GetID() == id) 
		{
			Saved_Redo->SetSelected(true);
		}

	pManager->DeleteFigure();
}
void AddHexAction::RedoActions()
{
	if (Saved_Redo->IsSelected()) 
	{
		pManager->SetSelectedFig(Saved_Redo);
	}
	pManager->AddFigure(Saved_Redo);
}
bool AddHexAction::CanBeRecorded() const
{
	return true;
}
AddHexAction::~AddHexAction()
{
	if (Saved_Redo)
		delete Saved_Redo;
}