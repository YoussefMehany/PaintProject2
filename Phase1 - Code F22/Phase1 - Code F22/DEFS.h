#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRIANGLE,
	DRAW_SQUARE,
	DRAW_HEX,
	DRAW_CIRC,
	CLOSEFIG,
	GREENCLR,
	REDCLR,
	BLUECLR,
	ORANGECLR,
	YELLOWCLR,
	BLACKCLR,
	SELECT_FIGURE,
	MOVE_FIGURE,
	UNDO_ACTION,
	REDO_ACTION,
	DELETE_FIGURE,
	START_REC,
	STOP_REC,
	PLAY_REC,
	LOAD_PROGRESS,
	SAVE_PROGRESS,
	CLEAR_ALL,
	MODE_CONVERTER,
	CLOSECLR,
	DRAW_COLOR,		//display colors menu
	DRAW_FIGURE,	//display figures menu
	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	PICK_TYPE,
	PICK_CLR,
	PICK_TYPECLR,
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS			//A click on the status bar

	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif