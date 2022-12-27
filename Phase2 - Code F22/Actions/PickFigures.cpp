#include "PickFigures.h"

PickFigures::PickFigures(ApplicationManager* pApp) :Action(pApp)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	CCounter = 0;
	FCounter = 0;
}
//Reads parameters required for action to execute (code depends on action type)
void PickFigures::ReadActionParameters()
{
	pManager->SetKEY(true);
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
void PickFigures::Execute()
{
	ReadActionParameters();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Pick_a_figure.wav"), NULL, SND_SYNC);
	}
	CFigure* select = NULL;
	int figcount = pManager->getFigCount();
	FigType = pManager->GetRandomFig();
	if (FigType == noshape)
	{
		pOut->PrintMessage("NO FIGURES");
		pManager->SetRandFigCount(0);
		pManager->UnBlock();
		pManager->SetKEY(false);
		return;
	}
	pManager->UpdateInterface();
	pOut->PrintMessage("Pick All " + TypetoString(FigType));
	for (int i = 0; i < figcount; i++)
	{
		pIn->GetPointClicked(P.x, P.y);
		select = pManager->GetFigure(P);
		if (!select)
		{
			i--;
			continue;
		}
		if (select->GetFigType() == FigType)
		{
			CCounter++;
		}
		else
		{
			FCounter++;
		}
		pOut->PrintMessage("Correct : " + to_string(CCounter) + "      Incorrect : " + to_string(FCounter));

		if (CCounter == pManager->GetRandFigCount())
			break;

		pManager->BlockFig(select);
		pManager->UpdateInterface();
	}
	pManager->SetRandFigCount(0);
	pManager->SetTypeClrCount(0);
	pManager->UnBlock();
	pManager->SetKEY(false);
}
string PickFigures::TypetoString(shape FigType) {
	if (FigType == hexagon) return "Hexagons";
	if (FigType == triangle) return "Triangles";
	if (FigType == square) return "Squares";
	if (FigType == rectangle) return "Rectangles";
	if (FigType == circle) return "Circles";
}