#include "Action.h"
#include "../ApplicationManager.h"
class MoveByDragAction :public Action
{
private:
	Point P;
	Point P_Rec;
	CFigure* Saved;
	CFigure* Saved_Redo;
public:
	MoveByDragAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~MoveByDragAction();
};
