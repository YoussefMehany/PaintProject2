#include "FigureMenuAction.h"

FigureMenuAction::FigureMenuAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void FigureMenuAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->Figure_menu();
}

//Execute action (code depends on action type)
void FigureMenuAction::Execute()
{
	ReadActionParameters();
}