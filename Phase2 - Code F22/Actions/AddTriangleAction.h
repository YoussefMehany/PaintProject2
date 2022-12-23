#ifndef ADD_TRIANGLE_ACTION_H
#define ADD_TRIANGLE_ACTION_H

#include "Action.h"
//#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"
//Add Triangle Action class
class AddTriangleAction : public Action
{
private:
	Point P1, P2, P3; //Triangle Corners
	Point P1_Rec, P2_Rec, P3_Rec;
	GfxInfo TriangleGfxInfo;
	CFigure* Saved;
public:
	AddTriangleAction(ApplicationManager* pApp);

	//Reads Triangle parameters
	virtual void ReadActionParameters();

	//Add Triangle to the ApplicationManager
	virtual void Execute();
	virtual void UndoActions();
	virtual void RedoActions();
};

#endif