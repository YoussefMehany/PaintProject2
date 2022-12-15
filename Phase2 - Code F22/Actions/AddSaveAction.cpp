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

	pOut->PrintMessage("Enter the file name ");


	fileName = pIn->GetSrting(pOut) + ".txt";
	OutFile.open(fileName);
}

void AddSaveAction::Execute()
{
	ReadActionParameters();

	int FiguresCount = pManager->getFigCount();
	string DrawClr = getColor(UI.DrawColor);
	string FillClr;
	if (UI.IsFilled) FillClr = getColor(UI.FillColor);
	else FillClr = "NO_FILL";
	OutFile << DrawClr << '\t' << FillClr << '\n' << FiguresCount << '\n';
	pManager->SaveFile(OutFile);
	OutFile.close();
}

string AddSaveAction::getColor(color clr)
{
	if (clr == BLUE)
	{
		return "BLUE";
	}
	if (clr == GREEN)
	{
		return "GREEN";
	}
	if (clr == WHITE) 
	{
		return "WHITE";
	}
	if (clr == RED)
	{
		return "RED";
	}
	if (clr == BLACK)
	{
		return "BLACK";
	}
	if (clr == ORANGE)
	{
		return "ORANGE";
	}
	if (clr == YELLOW)
	{
		return "YELLOW";
	}
}