#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void UpdateToolBar() const; //Updates the toolbar with the right Mood
	void Figure_menu() const;
	void Color_menu() const;
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawTrig(Point P1, Point P2, Point P3, GfxInfo TrigGfxInfo, bool selected = false) const; //Draw a triangle (Marwan)
	void DrawCir(Point P1, Point P2, GfxInfo CirGfxInfo, bool selected = false) const; //Draw a circle (Marwan)
	void DrawHex(Point P1, GfxInfo HexGfxInfo, bool selected = false) const; //Draw a circle (Youssef)
	void DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected = false) const; //Draw a Square (Youssef)
	///Make similar functions for drawing all other figure types.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width

	
	~Output();
};

#endif