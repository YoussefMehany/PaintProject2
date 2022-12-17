#include "ColorMenu.h"

ColorMenu::ColorMenu(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ColorMenu::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->Color_menu();
}

//Execute action (code depends on action type)
void ColorMenu::Execute()
{
	ReadActionParameters();
}