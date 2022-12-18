#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
	
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case FIGURES: return DRAW_FIGURE;
			case SELECT: return SELECT_FIGURE;
			case PAINT:  return FILL_COLOR;
			case BORDER:  return BORDER_COLOR;
			case MOVE: return MOVE_FIGURE;
			case UNDO: return UNDO_ACTION;
			case REDO: return REDO_ACTION;
			case DELETe: return DELETE_FIGURE;
			case START: return START_REC;
			case STOP: return STOP_REC;
			case PLAY: return PLAY_REC;
			case LOAD: return LOAD_PROGRESS;
			case SAVE: return SAVE_PROGRESS;
			case CLEAR: return CLEAR_ALL;
			case SWITCH_PLAY: return TO_PLAY;
			case ITM_EXIT: return EXIT;	
			
			default: return EMPTY;
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_FIGURE) {
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;

			case ITM_CIRC: return DRAW_CIRC;

			case ITM_TRIANGLE: return DRAW_TRIANGLE;

			case ITM_SQUARE: return DRAW_SQUARE;

			case ITM_HEX: return DRAW_HEX;

			case FIGURE: return RETURN;

			default: return EMPTY;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_COLOR)
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			case CLR_GREEN: return GREENCLR;

			case CLR_RED: return REDCLR;

			case CLR_BLUE: return BLUECLR;

			case CLR_ORANGE: return ORANGECLR;

			case CLR_YELLOW: return YELLOWCLR;

			case CLR_BLACK: return BLACKCLR;

			case COLORS: return RETURN;

			default: return EMPTY;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			case PLAYTYPE: return PICK_TYPE;

			case PLAYCLR: return PICK_CLR;

			case PLAYTYPECLR: return PICK_TYPECLR;

			case SWITCH_DRAW: return TO_DRAW;

			default: return EMPTY;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}	

}
/////////////////////////////////
	
Input::~Input()
{
}
