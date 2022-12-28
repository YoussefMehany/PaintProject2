#include"SaveAction.h"
#include "../ApplicationManager.h"

SaveAction::SaveAction(ApplicationManager* pApp) :Action(pApp)
{
}

void SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Save.wav"), NULL, SND_SYNC);
	}
	pOut->PrintMessage("Enter the file name ");


	fileName = pIn->GetSrting(pOut) + ".txt";
	OutFile.open(fileName);
	pOut->PrintMessage("File saved");
}

void SaveAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}

	int FiguresCount = pManager->getFigCount();
	string DrawClr = getColor(UI.DrawColor);
	string FillClr;
	if (UI.IsFilled) FillClr = getColor(UI.FillColor);
	else FillClr = "NO_FILL";
	OutFile << DrawClr << '\t' << FillClr << '\n' << FiguresCount << '\n';
	pManager->SaveFile(OutFile);
	OutFile.close();
}
bool SaveAction::CanBeRecorded() const
{
	return false;
}
string SaveAction::getColor(color clr)
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