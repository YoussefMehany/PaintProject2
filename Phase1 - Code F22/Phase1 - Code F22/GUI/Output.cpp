#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 51;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[SELECT] = "images\\MenuItems\\SELECT.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\Menu_Triangle.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\Menu_Square.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\Menu_Hex.jpg";
	//MenuItemImages[PIANT] = "images\\MenuItems\\PIANT2.jpg";
	MenuItemImages[CLR_GREEN] = "images\\MenuItems\\GREEN.jpg";
	MenuItemImages[CLR_RED] = "images\\MenuItems\\RED.jpg";
	MenuItemImages[CLR_BLUE] = "images\\MenuItems\\BLUE.jpg";
	MenuItemImages[CLR_ORANGE] = "images\\MenuItems\\ORANGE.jpg";
	MenuItemImages[CLR_YELLOW] = "images\\MenuItems\\YELLOW.jpg";
	MenuItemImages[CLR_BLACK] = "images\\MenuItems\\BLACK.jpg";
	MenuItemImages[MOVE] = "images\\MenuItems\\MOVE.jpg";
	MenuItemImages[UNDO] = "images\\MenuItems\\UNDO.jpg";
	MenuItemImages[REDO] = "images\\MenuItems\\REDO.jpg";
	MenuItemImages[DELETe] = "images\\MenuItems\\DELETE.jpg";
	MenuItemImages[START] = "images\\MenuItems\\START.jpg";
	MenuItemImages[STOP] = "images\\MenuItems\\STOP.jpg";
	MenuItemImages[PLAY] = "images\\MenuItems\\PLAY.jpg";
	MenuItemImages[LOAD] = "images\\MenuItems\\LOAD.jpg";
	MenuItemImages[SAVE] = "images\\MenuItems\\SAVE.jpg";
	MenuItemImages[CLEAR] = "images\\MenuItems\\CLEAR2.jpg";
	MenuItemImages[SWITCH] = "images\\MenuItems\\SWITCH.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\EXIT.jpg";


	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,1);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}
void Output::DrawTrig(Point P1, Point P2, Point P3, GfxInfo TrigGfxInfo, bool selected)const
{

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TrigGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (TrigGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TrigGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}
void Output::DrawCir(Point P1, Point P2, GfxInfo CirGfxInfo, bool selected)const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CirGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (CirGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CirGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int Radius = 0;
	Radius = sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2));
	pWind->DrawCircle(P1.x, P1.y, Radius, style);
	if (P1.y - Radius < UI.ToolBarHeight) 
	{
		pWind->SetPen(WHITE, 1);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(0,0, UI.width, UI.ToolBarHeight);
		CreateDrawToolBar();
	}
}
void Output::DrawHex(Point P1, GfxInfo HexGfxInfo, bool selected)const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int Side = 100;
	int Px[6];
	int Py[6];
	Px[0] = P1.x + Side, Px[1] = P1.x + Side, Px[2] = P1.x, Px[3] = P1.x - Side;
	Px[4] = P1.x - Side, Px[5] = P1.x;
	Py[0] = P1.y - Side / 2, Py[1] = P1.y + Side / 2, Py[2] = P1.y + Side, Py[3] = P1.y + Side / 2;
	Py[4] = P1.y - Side / 2, Py[5] = P1.y - Side;
	pWind->DrawPolygon(Px, Py, 6, style);
	if (P1.y - Side < UI.ToolBarHeight)
	{
		pWind->SetPen(WHITE, 1);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
		CreateDrawToolBar();
	}
}
void Output::DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected)const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int Side = 200;
	Point P2, P3;
	P2.x = P1.x - Side / 2, P2.y = P1.y - Side / 2;
	P3.x = P1.x + Side / 2, P3.y = P1.y + Side / 2;
	pWind->DrawRectangle(P2.x, P2.y, P3.x, P3.y, style);
	if (P2.y < UI.ToolBarHeight)
	{
		pWind->SetPen(SNOW, 1);
		pWind->SetBrush(SNOW);
		pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
		CreateDrawToolBar();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

