#ifndef ADD_HEX_ACTION_H
#define ADD_HEX_ACTION_H

#include "Action.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"
//Add Hexagon Action class
class AddHexAction : public Action
{
private:
	Point P1; //Hexagon Corners
	GfxInfo HexGfxInfo;
	CFigure* Saved_Redo;
public:
	AddHexAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual bool Execute(bool ReadParams = true);
	virtual void UndoActions();
	virtual void RedoActions();
	virtual bool CanBeRecorded() const;
	~AddHexAction();
};

#endif