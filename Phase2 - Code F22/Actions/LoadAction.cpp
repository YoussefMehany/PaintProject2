#include"LoadAction.h"
#include "../ApplicationManager.h"
LoadAction::LoadAction(ApplicationManager* pApp) :Action(pApp)
{
}

void LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter the file name ");

	fileName = pIn->GetSrting(pOut) + ".txt";
	InFile.open(fileName);
	if (InFile.is_open())
	{
		pOut->PrintMessage("File Loaded");
	}
	else 
	{
		pOut->PrintMessage("Error, file doesn't exist");
	}
}

void LoadAction::Execute()
{
	ReadActionParameters();
	pManager->ClearAll();
	if (InFile.is_open())
	{
		string Word;
		InFile >> Word;
		UI.DrawColor = getColorr(Word);
		InFile >> Word;
		if (Word != "NO_FILL") {
			UI.IsFilled = true;
			UI.FillColor = getColorr(Word);
		}
		InFile >> Word;
		int FigureCount = stoi(Word);
		for (int i = 0; i < FigureCount; i++)
		{
			InFile >> Word;
			CreateFigure(Word);
		}
		InFile.close();
	}
}
void LoadAction::CreateFigure(string Word) 
{
	if (Word[0] == '0') 
	{
		CHexagon* Fig = new CHexagon();
		Fig->Load(InFile);
		pManager->AddFigure(Fig);
	}
	if (Word[0] == '1')
	{
		CRectangle* Fig = new CRectangle();
		Fig->Load(InFile);
		pManager->AddFigure(Fig);
	}
	if (Word[0] == '2')
	{
		CTriangle* Fig = new CTriangle();
		Fig->Load(InFile);
		pManager->AddFigure(Fig);
	}
	if (Word[0] == '3')
	{
		CCircle* Fig = new CCircle();
		Fig->Load(InFile);
		pManager->AddFigure(Fig);
	}
	if (Word[0] == '4')
	{
		CSquare* Fig = new CSquare();
		Fig->Load(InFile);
		pManager->AddFigure(Fig);
	}
}
color LoadAction::getColorr(string clr)
{
	if (clr == "BLUE")
	{
		return BLUE;
	}
	if (clr == "GREEN")
	{
		return GREEN;
	}
	if (clr == "WHITE")
	{
		return WHITE;
	}
	if (clr == "RED")
	{
		return RED;
	}
	if (clr == "BLACK")
	{
		return BLACK;
	}
	if (clr == "ORANGE")
	{
		return ORANGE;
	}
	if (clr == "YELLOW")
	{
		return YELLOW;
	}
}