#include <windows.h> 
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
#include "Actions\StopRecAction.h"
#include "Actions\PlayRecAction.h"
#include "Actions\FigureMenuAction.h"
#include "Actions\ColorMenuAction.h"
#include "Actions\ReturnAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions/RedoAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	Recording = false;
	PlayingRec = false;
	Undo = false;
	Redo = false;
	FigCount = 0;
	
	RecCount = 0;
	UndoCount = 0;
	RedoCount = 0;
	ListCounter_Undo = 0;
	ListCounter_Redo = 0;

	CheckUpdate = false;
	LastAction = START_PROGRAM;
	//Create an array of figure pointers and set them to NULL		
	for(int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;	
	for (int i = 0; i < MaxRecCount; i++)
		Recorded[i] = NULL;
	for (int i = 0; i < MaxUndoCount; i++)
		SaveUndoActions[i]= NULL;
	for (int i = 0; i < MaxRedoCount; i++)
		SaveRedoActions[i] = NULL;

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
			pAct = new FigureMenuAction(this);
			break;

		case FILL_COLOR: //expanding the fill colors menu
			pAct = new ColorMenuAction(this, PAINT);
			break;

		case BORDER_COLOR: //expanding the border colors menu
			pAct = new ColorMenuAction(this, BORDER);
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

		case RETURN:
			pAct = new ReturnAction(this);
			break;

		case UNDO_ACTION:
			if (FigCount == 0 &&ListCounter_Undo==0) {
				
				pOut->PrintMessage("No Action to undo");
				break;
			}
			if (UndoCount ==5&&LastAction==UNDO_ACTION)
			{
				
				pOut->PrintMessage("Undo Limit Exceeded,Please make anothr action frist");
				
				break;
			}
			SetUndo(true);
			pOut->PrintMessage("Undoed   "+to_string(ListCounter_Undo - UndoCount - 1));
			Sleep(1000);
			pAct = new UndoAction(this);
			break;
		case REDO_ACTION:
			if (LastAction != UNDO_ACTION) 
			{ 
				pOut->PrintMessage("No Undo to Redo"); 
				break; 
			}
			pAct = new RedoAction(this);
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
			if (LastAction != START_PROGRAM && LastAction != CLEAR_ALL) {
				pOut->PrintMessage("You can only record after the program start or after clear all");
				break;
			}
			pAct = new StartRecAction(this);
			break;

		case STOP_REC:
			if (!Recording) {
				pOut->PrintMessage("Record some actions first");
				break;
			}
			pAct = new StopRecAction(this);
			break;

		case PLAY_REC:
			if (Recording) {
				pOut->PrintMessage("Stop the recording first");
				break;
			}
			pAct = new PlayRecAction(this);
			break;

		case CLEAR_ALL:
			pAct = new ClearAllAction(this);
			break;

		case EXIT:
			///create ExitAction here

			break;
	}
	
	if(pAct != NULL)
	{
		LastAction = ActType;
		CheckUpdate = true;
		pAct->Execute(); //Execute
		if (Recording && ActType < 30) // all the action types that can be recorded
		{
			if (RecCount < MaxRecCount)
				Recorded[RecCount++] = pAct;
		}
		if (ActType >= 1 && ActType <= 14)
		{
			SaveUndoActions[ListCounter_Undo -UndoCount] = pAct;
			ListCounter_Undo++;
			RedoCount = 0;
		}
		SetUndo(false);
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
void ApplicationManager::UndoLastAction()
{
	ClearAll();
	for (int i = 0; i < ListCounter_Undo - UndoCount - 1; i++)
	{
		SaveUndoActions[i]->Execute();
	}
	for (int i = ListCounter_Undo - 1; i >= ListCounter_Undo - UndoCount - 1; i--)
		SaveRedoActions[ListCounter_Redo++] = SaveUndoActions[i];
	UndoCount++;
}
void ApplicationManager::RedoLastAction()
{
	for (int i = 0; i < ListCounter_Redo - RedoCount ; i++)
	{
		SaveRedoActions[i]->Execute();
	}
	RedoCount++;
}
CFigure* ApplicationManager::GetAddress(int id)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID() == id)
		{
			return FigList[i];
		}
	}
}
void ApplicationManager::DeleteFigure()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] == SelectedFig) {
			FigList[i] = FigList[--FigCount];
			SelectedFig->SetSelected(false);
			delete SelectedFig;
			SelectedFig = NULL;
			break;
		}
	}
	FigList[FigCount] = NULL;
}
void ApplicationManager::ClearAll()
{
	UI.IsFilled = false;
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	if (!PlayingRec&&!Undo) {
		for (int i = 0; i < RecCount; i++) {
			delete Recorded[i];
			Recorded[i] = NULL;
		}
		RecCount = 0;
	}
	if (!Undo) 
	{
		for (int i = 0; i < UndoCount; i++) {
			delete SaveUndoActions[i];
			SaveUndoActions[i] = NULL;
		}
		UndoCount = 0;
	}
	if (!Redo)
	{
		for (int i = 0; i < RedoCount; i++) {
			delete SaveRedoActions[i];
			SaveRedoActions[i] = NULL;
		}
		RedoCount = 0;
	}
	FigCount = 0;
	SelectedFig = NULL;
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
bool ApplicationManager::IsRecording() const {
	return Recording;
}
bool ApplicationManager::IsPlayingRec() const {
	return PlayingRec;
}
bool ApplicationManager::IsUndoAction() const {
	return Undo;
}
bool ApplicationManager::IsRedoAction() const {
	return Redo;
}
void ApplicationManager::SetRec(bool IsRec)
{
	Recording = IsRec;
}
void ApplicationManager::SetUndo(bool IsUndo)
{
	Undo = IsUndo;
}
void ApplicationManager::SetRedo(bool IsRedo)
{
	Redo = IsRedo;
}

void ApplicationManager::PlayRec() {
	PlayingRec = true;
	ClearAll();
	for (int i = 0; i < RecCount; i++) {
		Sleep(1000);
		Recorded[i]->Execute();
		UpdateInterface();
	}
	PlayingRec = false;
}
void ApplicationManager::PrintLastMsg()
{
	switch (LastAction)
	{
	case SAVE_PROGRESS:
		pOut->PrintMessage("File Saved");
		break;

	case START_REC:
		pOut->PrintMessage("Recording Started");
		break;

	case STOP_REC:
		pOut->PrintMessage("Recording Stopped");
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
