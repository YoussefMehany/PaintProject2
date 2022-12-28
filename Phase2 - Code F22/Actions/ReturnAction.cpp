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
void ReturnAction::Execute(bool ReadParams)
{
	if (ReadParams) {
		ReadActionParameters();
	}
}
bool ReturnAction::CanBeRecorded() const
{
	return true;
}