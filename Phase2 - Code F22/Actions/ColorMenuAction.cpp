#include "ColorMenuAction.h"

ColorMenuAction::ColorMenuAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ColorMenuAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->Color_menu();
}

//Execute action (code depends on action type)
void ColorMenuAction::Execute()
{
	ReadActionParameters();
}