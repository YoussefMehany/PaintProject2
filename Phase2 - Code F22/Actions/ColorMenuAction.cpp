#include "ColorMenuAction.h"

ColorMenuAction::ColorMenuAction(ApplicationManager* pApp, DrawMenuItem choose) :Action(pApp)
{
	ChooseMenuItem = choose;
}
//Reads parameters required for action to execute (code depends on action type)
void ColorMenuAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	UI.Choose = ChooseMenuItem;
	pOut->Color_menu();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Choose_a_color.wav"), NULL, SND_SYNC);
	}
}

//Execute action (code depends on action type)
void ColorMenuAction::Execute()
{
	ReadActionParameters();
}