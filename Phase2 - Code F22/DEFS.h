#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	START_PROGRAM,
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRIANGLE,
	DRAW_SQUARE,
	DRAW_HEX,
	DRAW_CIRC,
	GREENCLR,
	REDCLR,
	BLUECLR,
	ORANGECLR,
	YELLOWCLR,
	BLACKCLR,
    MOVE_FIGURE,
    DELETE_FIGURE,
	SELECT_FIGURE,
	RETURN,
	UNDO_ACTION,
	REDO_ACTION,
	CLEAR_ALL,
	MODE_CONVERTER,
	CLOSECLR,
	FILL_COLOR,
	BORDER_COLOR,
	DRAW_FIGURE,	//display figures menu
	PICK_TYPE,
	PICK_CLR,
	PICK_TYPECLR,
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	START_REC,
	STOP_REC,
	PLAY_REC,
	LOAD_PROGRESS,
	SAVE_PROGRESS,
	TO_PLAY, //Switch interface to Play mode
	TO_DRAW,		//Switch interface to Draw mode
	EXIT,
	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{
	int x, y;
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};
enum shape
{
	hexagon,
	rectangle,
	triangle,
	circle,
	square
};
#endif