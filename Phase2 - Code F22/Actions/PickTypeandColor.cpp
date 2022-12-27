#include "PickTypeandColor.h"


PickTypeandColor::PickTypeandColor(ApplicationManager* pApp) :Action(pApp)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	CCounter = 0;
	FCounter = 0;
	Random = 0;
}
//Reads parameters required for action to execute (code depends on action type)
void PickTypeandColor::ReadActionParameters()
{
	pManager->SetKEY(true);
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
void PickTypeandColor::Execute()
{
	ReadActionParameters();
	pManager->UpdateInterface();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Pick_a_figure_with_a_color.wav"), NULL, SND_SYNC);
	}
	CFigure* select = NULL;
	shape SelectedType;
	int figcount = pManager->getFigCount();
	color = pManager->GetRandomClr(Random);
	if (color == "NO COLORED FIG")
	{
		pOut->PrintMessage("NO COLORED FIGURE");
		pManager->SetClrCount(0);
		pManager->UnBlock();
		pManager->SetKEY(false);
	}
	FigType = pManager->GetRandomFig(Random);
	pOut->PrintMessage("Pick All " + TypetoString(FigType) + "with " + color + "color");
	for (int i = 0; i < figcount; i++)
	{
		pIn->GetPointClicked(P.x, P.y);
		select = pManager->GetFigure(P);
		if (!select)
		{
			i--;
			continue;
		}
		if (dynamic_cast<CRectangle*>(select)) {
			SelectedType = rectangle;
		}
		else if (dynamic_cast<CTriangle*>(select)) {
			SelectedType = triangle;
		}
		else if (dynamic_cast<CSquare*>(select)) {
			SelectedType = square;
		}
		else if (dynamic_cast<CCircle*>(select)) {
			SelectedType = circle;
		}
		else if (dynamic_cast<CHexagon*>(select)) {
			SelectedType = hexagon;
		}
		if (SelectedType == FigType && select->getColor() == color)
		{
			CCounter++;
		}
		else
		{
			FCounter++;
		}
		pOut->PrintMessage("Correct : " + to_string(CCounter) + "      Incorrect : " + to_string(FCounter));

		if (CCounter == pManager->GetClrCount())
			break;

		pManager->BlockFig(select);
		pManager->UpdateInterface();
	}
	pManager->SetRandFigCount(0);
	pManager->SetClrCount(0);
	pManager->UnBlock();
	pManager->SetKEY(false);
}
string PickTypeandColor::TypetoString(shape FigType) {
	if (FigType == hexagon) return "Hexagons";
	if (FigType == triangle) return "Triangles";
	if (FigType == square) return "Squares";
	if (FigType == rectangle) return "Rectangles";
	if (FigType == circle) return "Circles";
}