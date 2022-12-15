#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddHexAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\AddUndoAction.h"
#include "Actions\AddMoveAction.h"
#include "Actions\AddSelectAction.h"
#include "Actions\AddChangeColorAction.h"
#include "Actions\AddDeleteAction.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	FigCount = 0;
	CheckUpdate = false;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	CheckUpdate = false;
	switch (ActType)
	{
		case DRAW_FIGURE: //expanding the figures menu
			pOut->PrintMessage("Action: a click on the figures menu, Click anywhere");
			pOut->Figure_menu();
			break;

		case DRAW_COLOR: //expanding the figures menu
			pOut->PrintMessage("Action: a click on the figures menu, Click anywhere");
			pOut->Color_menu();
			break;

		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			break;

		case DRAW_HEX:
			pAct = new AddHexAction(this);
			break;

		case DRAW_TRIANGLE:
			pAct = new AddTriangleAction(this);
			break;

		case DRAW_SQUARE:
			pAct = new AddSquareAction(this);
			break;

		case CLOSEFIG:
			pOut->PrintMessage("Action: a click on back button, Click anywhere");
			pOut->CreateDrawToolBar();
			break;

		case UNDO_ACTION:
			pAct = new AddUndoAction(this);
			break;

		case MOVE_FIGURE:
			
			if (SelectedFig == NULL){
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddMoveAction(this);
			break;

		case SELECT_FIGURE:
			pAct = new AddSelectAction(this);
			break;

		case STATUS:	//a click on the status bar ==> no action
			return;

		case GREENCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddChangeColorAction(this, GREEN);
			break;

		case REDCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddChangeColorAction(this, RED);
			break;

		case BLUECLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddChangeColorAction(this, BLUE);
			break;

		case ORANGECLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddChangeColorAction(this, ORANGE);
			break;

		case YELLOWCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddChangeColorAction(this, YELLOW);
			break;

		case BLACKCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddChangeColorAction(this, BLACK);
			break;

		case CLOSECLR:
			pOut->PrintMessage("Action: a click on back button, Click anywhere");
			pOut->CreateDrawToolBar();
			break;

		case DELETE_FIGURE:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new AddDeleteAction(this);
			break;
		
		case EXIT:
			///create ExitAction here

			break;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		CheckUpdate = true;
		pAct->Execute(); //Execute
		delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(Point P1) const
{
	//If a figure is found return a pointer to it.
	//if this point does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
	CFigure* FigurePtr = NULL;
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsPointInside(P1)) {
			if (SelectedFig == FigList[i]) {
				SelectedFig->SetSelected(true);
				FigurePtr = FigList[i];
			}
			else {
				if (SelectedFig) SelectedFig->SetSelected(false);
				FigurePtr = FigList[i];
			}
		}
	}
	return FigurePtr;
}
void ApplicationManager::MoveFigure(Point P1)
{
	SelectedFig->MoveTo(P1);
}

void ApplicationManager::DeleteFigure()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] == SelectedFig) {
			FigList[i] = FigList[--FigCount];
			delete SelectedFig;
			SelectedFig = NULL;
			break;
		}
	}
	FigList[FigCount] = NULL;
}
void ApplicationManager::SelectFigure(Point P1)
{
	CFigure* FigPtr = GetFigure(P1);
	if (FigPtr) {
		SelectedFig = FigPtr;
		if (SelectedFig) {
			SelectedFig->SetSelected(!SelectedFig->IsSelected());
			if (!SelectedFig->IsSelected()) {
				SelectedFig = NULL;
			}
		}
	}
}

void ApplicationManager::ChangeColor(color clr)
{
	if (UI.Choose == BORDER) SelectedFig->ChngDrawClr(clr);
	else SelectedFig->ChngFillClr(clr);
}

//////////////////////////////////////////////////////////////////////////////////////

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	if (CheckUpdate) {
		pOut->ClearDrawArea();
		for (int i = 0; i < FigCount; i++)
			FigList[i]->Draw(pOut); //Call Draw function (virtual member fn)
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
