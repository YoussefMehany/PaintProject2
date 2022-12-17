#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddHexAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\UndoAction.h"
#include "Actions\MoveAction.h"
#include "Actions\SelectAction.h"
#include "Actions\ChangeColorAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\SaveAction.h"
#include "Actions\StartRecAction.h"
#include "Actions\FigureMenu.h"
#include "Actions\ColorMenu.h"
#include "Actions\ReturnAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	FigCount = 0;
	RecCount = 0;
	UndoCount = 0;
	ListCounter = 0;
	CheckUpdate = false;
	//Create an array of figure pointers and set them to NULL		
	for(int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;	
	for (int i = 0; i < MaxRecCount; i++)
		Recorded[i] = NULL;
	for (int i = 0; i < MaxUndoCount; i++)
		UndoFigList[i] = NULL;
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
			pAct = new FigureMenu(this);
			break;

		case DRAW_COLOR: //expanding the figures menu
			pAct = new ColorMenu(this);
			break;

		case DRAW_RECT:
			pAct = new AddRectAction(this);
			UndoLast = DRAW_RECT;
			break;

		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			UndoLast = DRAW_CIRC;
			break;

		case DRAW_HEX:
			pAct = new AddHexAction(this);
			UndoLast = DRAW_HEX;
			break;

		case DRAW_TRIANGLE:
			pAct = new AddTriangleAction(this);
			UndoLast = DRAW_TRIANGLE;
			break;

		case DRAW_SQUARE:
			pAct = new AddSquareAction(this);
			UndoLast = DRAW_SQUARE;
			break;

		case RETURN:
			pAct = new ReturnAction(this);
			break;

		case UNDO_ACTION:
			if (FigCount == 0) {
				pOut->PrintMessage("No Action to undo");
				break;
			}
			if (UndoCount == 5)
			{
				pOut->PrintMessage("Undo Limit Exceeded");
				break;
			}
			pAct = new UndoAction(this);
			break;

		case MOVE_FIGURE:
			
			if (SelectedFig == NULL){
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new MoveAction(this);
			break;

		case SELECT_FIGURE:
			pAct = new SelectAction(this);
			break;

		case STATUS:	//a click on the status bar ==> no action
			return;

		case GREENCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new ChangeColorAction(this, GREEN);
			break;

		case REDCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new ChangeColorAction(this, RED);
			break;

		case BLUECLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			
			pAct = new ChangeColorAction(this, BLUE);
			break;

		case ORANGECLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new ChangeColorAction(this, ORANGE);
			break;

		case YELLOWCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new ChangeColorAction(this, YELLOW);
			break;

		case BLACKCLR:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new ChangeColorAction(this, BLACK);
			break;

		case DELETE_FIGURE:
			if (SelectedFig == NULL) {
				pOut->PrintMessage("Please Select a Figure First");
				break;
			}
			pAct = new DeleteAction(this);
			break;

		case SAVE_PROGRESS:
			pAct = new SaveAction(this);
			break;

		case START_REC:
			pAct = new StartRecAction(this);
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
		LastAction = ActType;
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
	if (FigCount < MaxFigCount) {
		FigList[FigCount++] = pFig;
		pFig->SetID(FigCount);
	}
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
ActionType ApplicationManager::getLastAction() const
{
	return UndoLast;
}
void ApplicationManager::UndoLastAction(ActionType Act)
{
	CFigure* save = SelectedFig;
	
	switch (Act) 
	{
	case ADD_FIG:
		AddFigure(UndoFigList[4-UndoCount]);
		break;
	case DELETE_FIGURE:
		SelectedFig = FigList[FigCount - 1];
		DeleteFigure();
		SelectedFig = save;
		break;
	case CHANGE_CLR:

		break;
	case BACK_TO:

		break;
	}
	UndoCount++;
}
void ApplicationManager::DeleteFigure()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] == SelectedFig) {
			FigList[i] = FigList[--FigCount];
			
			if (ListCounter<5)
			    UndoFigList[ListCounter++]= SelectedFig;
			else
			{
				for (int i = 0; i < ListCounter-1; i++) 
				{
					UndoFigList[i] = UndoFigList[i + 1];
				}
				UndoFigList[ListCounter-1] = SelectedFig;
			}
			//delete SelectedFig;
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
	if (UI.Choose == BORDER)
	{
		UI.DrawColor = clr;
		SelectedFig->ChngDrawClr(UI.DrawColor);
	}
	else 
	{
		UI.IsFilled = true;
		UI.FillColor = clr;
		SelectedFig->ChngFillClr(UI.FillColor);
	}
}
int ApplicationManager::getFigCount()const {
	return FigCount;
}

void ApplicationManager::PrintLastMsg()
{
	switch (LastAction)
	{
	case SAVE_PROGRESS:
		pOut->PrintMessage("File Saved");
		break;
	}
		
}
//==================================================================================//
//							Save/Load Functions										//
//==================================================================================//

void ApplicationManager::SaveFile(ofstream& OutFile)
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
}

//////////////////////////////////////////////////////////////////////////////////////

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface()
{	
	if (CheckUpdate) {
		pOut->ClearDrawArea();
		for (int i = 0; i < FigCount; i++)
			FigList[i]->Draw(pOut); //Call Draw function (virtual member fn)
	}
	PrintLastMsg();
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
