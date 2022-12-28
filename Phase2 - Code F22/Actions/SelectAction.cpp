#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void SelectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
    if (pManager->IsSoundOn()) {
        PlaySound(TEXT("Sound/Select.wav"), NULL, SND_SYNC);
    }
	pOut->PrintMessage("New Position : Click on any figure");
	if (pManager->IsPlayingRec())
		P = P_Rec;
	else {
		pIn->GetPointClicked(P.x, P.y);
		P_Rec = P;
	}
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void SelectAction::Execute(bool ReadParams)
{
    if (ReadParams) {
        ReadActionParameters();
    }
    Output* pOut = pManager->GetOutput();
    CFigure* FigPtr = pManager->GetFigure(P);
    CFigure* SelectedFig = pManager->GetSelectedFig();
    if (FigPtr) {
        if (FigPtr->IsSelected()) {
            FigPtr->SetSelected(false);
            pManager->SetSelectedFig(NULL);
            pOut->PrintMessage("Figure unselected");
        }
        else {
            FigPtr->SetSelected(true);
            if (SelectedFig) SelectedFig->SetSelected(false);
            pManager->SetSelectedFig(FigPtr);
            FigPtr->PrintInfo(pOut);
        }
    }
    else {
        pOut->PrintMessage("A click on an empty area");
    }
}
bool SelectAction::CanBeRecorded() const
{
    return true;
}