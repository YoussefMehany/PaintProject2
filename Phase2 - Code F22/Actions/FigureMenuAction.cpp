#include "FigureMenuAction.h"

FigureMenuAction::FigureMenuAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void FigureMenuAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->Figure_menu();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Draw_a_figure.wav"), NULL, SND_SYNC);
	}
}

//Execute action (code depends on action type)
bool FigureMenuAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
	return false;
}
bool FigureMenuAction::CanBeRecorded() const
{
	return true;
}