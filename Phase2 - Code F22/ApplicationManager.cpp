#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddHexAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "AddUndoAction.h"
#include "AddMoveAction.h"
#include "AddSelectAction.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	FigCount = 0;
		
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
	switch (ActType)
	{
		case DRAW_FIGURE: //expanding the figures menu
			pOut->PrintMessage("Action: a click on the figures menu, Click anywhere");
			pOut->Figure_menu();
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

		case EXIT:
			///create ExitAction here
			
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
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
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
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}
void ApplicationManager::MoveFigure(Point P1)
{
	SelectedFig->MoveTo(P1);
}

void ApplicationManager::SelectFigure(Point P1)
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsPointInside(P1)) {
			if (FigList[i]->IsSelected()) {
				FigList[i]->SetSelected(false);
				SelectedFig = NULL;
			}
			else {
				if (SelectedFig) {
					SelectedFig->SetSelected(false);
				}
				FigList[i]->SetSelected(true);
				SelectedFig = FigList[i];
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
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