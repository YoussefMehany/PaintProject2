#ifndef ADD_SQUARE_ACTION_H
#define ADD_SQUARE_ACTION_H

#include "Action.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

//Add Square Action class
class AddSquareAction : public Action
{
private:
	Point P1; //Square Corners
	Point P1_Rec;
	GfxInfo SquareGfxInfo;
	CFigure* Saved;
public:
	AddSquareAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	virtual void UndoActions();
	virtual void RedoActions();
};

#endif