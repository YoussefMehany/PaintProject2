#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H

#include "Action.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

//Add Circle Action class
class AddCircAction : public Action
{
private:
	Point P1, P2; //Center and point on the circle
	Point P1_Rec, P2_Rec;
	GfxInfo CircGfxInfo;
	CFigure* Saved;
public:
	AddCircAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	virtual void UndoActions();
	virtual void RedoActions();
};

#endif