#include"AddSaveAction.h"
#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

AddSaveAction::AddSaveAction(ApplicationManager* pApp) :Action(pApp)
{
}

void AddSaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Enter name without spaces ");


	fileName = pIn->GetSrting(pOut) + ".txt";
	OutFile.open(fileName);
	if (OutFile.is_open())
	{
		pOut->PrintMessage("Your file has been Saved");
	}
	else {
		pOut->PrintMessage("Save failed");
	}
}

void AddSaveAction::Execute()
{
	ReadActionParameters();
	if (OutFile.is_open())
	{
		int FiguresCount = pManager->getFigCount();
		string DrawClr = getColorName(UI.DrawColor);
		OutFile << DrawClr;
		string FillClr = getColorName(UI.FillColor);
		OutFile << '\t' << FillClr << '\n' << FiguresCount << '\n' ;
		pManager->AssignIDS();
		pManager->SaveAll(OutFile);
		OutFile.close();
	}
}
//utility fn to return a string of the color 
string AddSaveAction::getColorName(color a)const
{

	if (a == RED)
	{
		return "RED";
	}

	if (a == BLACK)
	{
		return "BLACK";
	}

	if (a == BLUE)
	{
		return "BLUE";
	}

	if (a == GREEN)
	{
		return "GREEN";
	}

	if (a == WHITE)
	{
		return "WHITE";
	}
	return "NO";
}