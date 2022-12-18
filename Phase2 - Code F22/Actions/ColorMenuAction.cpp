#include "ColorMenuAction.h"

ColorMenuAction::ColorMenuAction(ApplicationManager* pApp, DrawMenuItem choose) :Action(pApp)
{
	ChooseMenuItem = choose;
}
//Reads parameters required for action to execute (code depends on action type)
void ColorMenuAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	UI.Choose = ChooseMenuItem;
	pOut->Color_menu();
}

//Execute action (code depends on action type)
void ColorMenuAction::Execute()
{
	ReadActionParameters();
}