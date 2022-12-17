#include "FigureMenu.h"

FigureMenu::FigureMenu(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void FigureMenu::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->Figure_menu();
}

//Execute action (code depends on action type)
void FigureMenu::Execute()
{
	ReadActionParameters();
}