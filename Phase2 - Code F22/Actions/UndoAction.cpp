#include "UndoAction.h"

UndoAction::UndoAction(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void UndoAction::ReadActionParameters()
{
	ActionType Action = pManager->getLastAction();
	switch (Action)
	{
	case DRAW_CIRC:
		Reverse_Last_Action = DELETE_FIGURE;
		break;
	case DRAW_HEX:
		Reverse_Last_Action = DELETE_FIGURE;
		break;
	case DRAW_RECT:
		Reverse_Last_Action = DELETE_FIGURE;
		break;
	case DRAW_TRIANGLE:
		Reverse_Last_Action = DELETE_FIGURE;
		break;
	case DRAW_SQUARE:
		Reverse_Last_Action = DELETE_FIGURE;
		break;
	case DELETE_FIGURE:
		Reverse_Last_Action = ADD_FIG;
		break;
	case GREENCLR:
		Reverse_Last_Action = CHANGE_CLR;
		break;

	case REDCLR:
		Reverse_Last_Action = CHANGE_CLR;
		break;

	case BLUECLR:
		Reverse_Last_Action = CHANGE_CLR;
		break;

	case ORANGECLR:
		Reverse_Last_Action = CHANGE_CLR;
		break;

	case YELLOWCLR:
		Reverse_Last_Action = CHANGE_CLR;
		break;

	case BLACKCLR:
		Reverse_Last_Action = CHANGE_CLR;
		break;
	case MOVE_FIGURE:
		Reverse_Last_Action = BACK_TO;
	}
	Output* pOut = pManager->GetOutput();
	if (Reverse_Last_Action == CHANGE_CLR) {
		if (UI.Choose == BORDER)
		{
			Reverse_Last_Action =CHANGE_DCLR;
			pOut->PrintMessage("Draw");
		}
		else
		{
			Reverse_Last_Action = CHANGE_FCLR;
			pOut->PrintMessage("Fill");
		}
	}
	Sleep(1000);
}

//Execute action (code depends on action type)
void UndoAction::Execute()
{
	ReadActionParameters();
	pManager->UndoLastAction(Reverse_Last_Action);
}
