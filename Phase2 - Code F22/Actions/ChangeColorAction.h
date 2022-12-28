#include "Action.h"
#include "../ApplicationManager.h"
class ChangeColorAction :public Action
{
	color colour;
	CFigure* Saved;
	CFigure* Saved_Redo;
public:
	ChangeColorAction(ApplicationManager* pApp, color clr);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~ChangeColorAction();
};
