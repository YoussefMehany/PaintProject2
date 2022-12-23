#include "AddHexAction.h"
//#include "..\Figures\CHexagon.h"

//#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddHexAction::AddHexAction(ApplicationManager* pApp) :Action(pApp)
{
}

void AddHexAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();



	//Read the center point
	pOut->PrintMessage("New Hexagon: Click at the Center");
	if (pManager->IsPlayingRec())
		P1 = P1_Rec;
	else {
		pIn->GetPointClicked(P1.x, P1.y);
		P1_Rec = P1;
	}
	pOut->ClearStatusBar();


	HexGfxInfo.isFilled = UI.IsFilled;
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexGfxInfo.FillClr = pOut->getCrntFillColor();



}

//Execute the action
void AddHexAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	//Create a rectangle with the parameters read from the user
	CHexagon* R = new CHexagon(P1, HexGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	id = R->GetID();
}
void AddHexAction::UndoActions()
{
	Saved = new CHexagon(P1, HexGfxInfo);
	Saved->SetID(id);
	pManager->DeleteLastFig();
}
void AddHexAction::RedoActions()
{
	pManager->AddFigure(Saved);
}