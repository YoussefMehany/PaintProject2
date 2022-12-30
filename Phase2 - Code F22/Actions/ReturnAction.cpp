#include "ReturnAction.h"

ReturnAction::ReturnAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ReturnAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();

}

//Execute action (code depends on action type)
bool ReturnAction::Execute(bool ReadParams)
{
	Output* pOut = pManager->GetOutput();
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	pOut->CreateDrawToolBar();
	return false;
}
bool ReturnAction::CanBeRecorded() const
{
	return true;
}