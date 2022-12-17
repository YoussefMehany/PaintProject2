#include "UndoAction.h"

UndoAction::UndoAction(ApplicationManager* pApp):Action(pApp)
{
	undo_action_count = 0;
}
//Reads parameters required for action to execute (code depends on action type)
 void UndoAction::ReadActionParameters()
 {
	


 }

//Execute action (code depends on action type)
 void UndoAction::Execute()
 {
	
 }
 