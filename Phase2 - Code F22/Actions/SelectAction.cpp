#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void SelectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
    if (UI.Sound)
    {
        PlaySound(TEXT("Sound/Select.wav"), NULL, SND_SYNC);
    }
	pOut->PrintMessage("New Position : Click on any figure");
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
bool SelectAction::Execute(bool ReadParams)
{
    if (ReadParams) 
    {
        ReadActionParameters();
    }
    Output* pOut = pManager->GetOutput();
    CFigure* FigPtr = pManager->GetFigure(P);
    CFigure* SelectedFig = pManager->GetSelectedFig();
    if (FigPtr) 
    {
        if (FigPtr->IsSelected())
        {
            FigPtr->SetSelected(false);
            pManager->SetSelectedFig(NULL);
            pOut->PrintMessage("Figure unselected");
        }
        else 
        {
            FigPtr->SetSelected(true);
            if (SelectedFig) SelectedFig->SetSelected(false);
            pManager->SetSelectedFig(FigPtr);
            FigPtr->PrintInfo(pOut);
        }
    }
    else 
    {
        pOut->PrintMessage("A click on an empty area");
    }
    if (pManager->IsRecording())
    {
        return false;
    }
    return true;
}
bool SelectAction::CanBeRecorded() const
{
    return true;
}