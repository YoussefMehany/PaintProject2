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
#include "Actions\LoadAction.h"
#include "Actions\StartRecAction.h"
#include "Actions\StopRecAction.h"
#include "Actions\PlayRecAction.h"
#include "Actions\FigureMenuAction.h"
#include "Actions\ColorMenuAction.h"
#include "Actions\ReturnAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions\RedoAction.h"
#include <iostream>
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
	Undo_RedoCount = 0;
	ListCounter_Undo_Redo = 0;
	ActionCount = 0;
	CheckUpdate = false;
	LastAction = START_PROGRAM;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	for (int i = 0; i < MaxRecCount; i++)
		Recorded[i] = NULL;
	for (int i = 0; i < MaxUndoCount; i++)
		SaveUndo_RedoActions[i] = NULL;

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
		if (ListCounter_Undo_Redo == 0)
		{
			pOut->PrintMessage("No Action to undo");
			break;
		}
		if (Undo_RedoCount == 5 && LastAction == UNDO_ACTION)
		{
			pOut->PrintMessage("Undo Limit Exceeded,Please make another action first");
			break;
		}
		pAct = new UndoAction(this);
		break;

	case REDO_ACTION:
		if ((LastAction != UNDO_ACTION && LastAction != REDO_ACTION) || Undo_RedoCount == 0)
		{
			pOut->PrintMessage("No Undo to Redo");
			break;
		}
		pAct = new RedoAction(this);
		break;

	case MOVE_FIGURE:

		if (SelectedFig == NULL) {
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

	case LOAD_PROGRESS:
		pAct = new LoadAction(this);
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

	if (pAct != NULL)
	{
		LastAction = ActType;
		CheckUpdate = true;
		pAct->Execute(); //Execute
		if (Recording && ActType < 30) // all the action types that can be recorded
		{
			if (RecCount < MaxRecCount)
				Recorded[RecCount++] = pAct;
			else
			{
				pOut->PrintMessage("recording stoped");
				Recording = false;
			}

		}
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
	}
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(Point P1) const
{
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->IsPointInside(P1)) {
			return FigList[i];
		}
	}
	return NULL;
}
void ApplicationManager::MoveFigure(Point P1)
{
	SelectedFig->MoveTo(P1);
}
void ApplicationManager::DeleteFigure(CFigure* F)
{
	CFigure* save = SelectedFig;
	if (F)
	{
		SelectedFig = F;
	}
	if (FigCount > 0)
	{
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i] == SelectedFig) {
				delete FigList[i];
				for (int j = i; j < FigCount - 1; j++) {
					FigList[j] = FigList[j + 1];
				}
				break;
			}
		}
		SelectedFig = NULL;
		FigList[--FigCount] = NULL;
	}
	if (F)
	{
		SelectedFig = save;
	}
}
void ApplicationManager::UndoLastAction()
{
	Undo_RedoCount++;
	SaveUndo_RedoActions[--ListCounter_Undo_Redo]->UndoActions();
}
void ApplicationManager::RedoLastAction()
{
	Undo_RedoCount--;
	SaveUndo_RedoActions[ListCounter_Undo_Redo++]->RedoActions();
}
void ApplicationManager::Add_Undo_Redo_Actions(Action* pAct)
{
	if (ListCounter_Undo_Redo < 5)
	{
		SaveUndo_RedoActions[ListCounter_Undo_Redo++] = pAct;
	}
	else
	{
		if (ActionCount > RecCount + MaxUndoCount) {
			delete SaveUndo_RedoActions[0];
		}
		SaveUndo_RedoActions[0] = NULL;
		for (int i = 0; i < ListCounter_Undo_Redo - 1; i++)
		{
			SaveUndo_RedoActions[i] = SaveUndo_RedoActions[i + 1];
		}
		SaveUndo_RedoActions[ListCounter_Undo_Redo - 1] = pAct;
	}
	ActionCount++;
	Undo_RedoCount = 0;
}
void ApplicationManager::DeleteLastFig()
{
	if (FigCount > 0)
	{
		int max = 0;
		int index = 0;
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i]->GetID() > max)
			{
				max = FigList[i]->GetID();
				index = i;
			}
		}
		delete FigList[index];
		FigList[index] = FigList[--FigCount];
		FigList[FigCount] = NULL;
	}
}
void ApplicationManager::SwapFigures(CFigure* F)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID() == F->GetID())
		{
			if (!SelectedFig || SelectedFig != FigList[i])
			{
				F->SetSelected(false);
			}
			else
				SetSelectedFig(F);
			delete FigList[i];
			FigList[i] = F;
			FigList[i]->ChngClr();
			break;
		}
	}
}
void ApplicationManager::ClearAll()
{
	UI.IsFilled = false;
	UI.DrawColor = BLUE;    //Drawing color
	UI.FillColor = GREEN;    //Filling color
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	int i = 0;
	if (ActionCount > RecCount + MaxUndoCount)
		i = 0;
	else
		i = 5 - (ActionCount - RecCount);
		for (; i < ListCounter_Undo_Redo; i++)
		{
			delete SaveUndo_RedoActions[i];
			SaveUndo_RedoActions[i] = NULL;
		}
	if (!PlayingRec) {
		for (int i = 0; i < RecCount; i++)
		{
			delete Recorded[i];
			Recorded[i] = NULL;
		}
		RecCount = 0;

	}
	ActionCount = 0;
	Undo_RedoCount = 0;
	ListCounter_Undo_Redo = 0;
	FigCount = 0;
	SelectedFig = NULL;
}
CFigure* ApplicationManager::GetSelectedFig()const
{
	return SelectedFig;
}
int ApplicationManager::getFigCount()const
{
	return FigCount;
}
bool ApplicationManager::IsRecording() const {
	return Recording;
}
bool ApplicationManager::IsPlayingRec() const {
	return PlayingRec;
}
void ApplicationManager::SetRec(bool IsRec)
{
	Recording = IsRec;
}
void ApplicationManager::SetSelectedFig(CFigure* F)
{
	SelectedFig = F;
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
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;

}
