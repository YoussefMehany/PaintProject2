#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <cmath>
#include <fstream>
//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	static int ID_Num;
	bool Selected;	//true if the figure is selected.
	bool Blocked;
	shape FigType;
	GfxInfo FigGfxInfo;	//Figure graphis info
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure::CFigure();
	void SetSelected(bool s);	//select/unselect the figure
	void SetBlock(bool);
	bool IsSelected() const;	//check whether fig is selected
	bool IsBlocked() const;
	void SetID(int id);
	int GetID()const;
	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	shape GetFigType() const;
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);  //changes the figure's filling color
	virtual void ChngClr()=0;	
	virtual void MoveTo(Point P)=0;
	virtual bool IsPointInside(Point P)=0;
	virtual CFigure* GetNewFigure()=0;
	
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	string getColor(color = BISQUE);
	color getColorr(string ="BISQUE");

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};
#endif