#include "ClearAllAction.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ClearAllAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void ClearAllAction::Execute()
{
	ReadActionParameters();

	pManager->ClearAll();
}