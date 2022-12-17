#include "PlayRecAction.h"

PlayRecAction::PlayRecAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void PlayRecAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

}

//Execute action (code depends on action type)
void PlayRecAction::Execute()
{
	ReadActionParameters();
	pManager->PlayRec();
}