#include "ColorMenuAction.h"

ColorMenuAction::ColorMenuAction(ApplicationManager* pApp, DrawMenuItem choose) :Action(pApp)
{
	ChooseMenuItem = choose;
}
//Reads parameters required for action to execute (code depends on action type)
void ColorMenuAction::ReadActionParameters()
{
	UI.Choose = ChooseMenuItem;
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Choose_a_color.wav"), NULL, SND_SYNC);
	}
}

//Execute action (code depends on action type)
bool ColorMenuAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pOut->Color_menu();
	return false;
}
bool ColorMenuAction::CanBeRecorded() const
{
	return true;
}
bool ColorMenuAction::CanBeDeleted() const
{
	return true;
}