#include <windows.h> 
#include <MMSystem.h>
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
#include "Actions/MoveByDragAction.h"
#include "Actions/ExitAction.h"
#include "Actions/SwitchToDrawAction.h"
#include "Actions/SwitchToPlayAction.h"
#include "Actions/PickColors.h"
#include "Actions/PickFigures.h"
#include "Actions/PickTypeandColor.h"
#include "Actions/ChangeSoundState.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	Recording = false;
	PlayingRec = false;
	PlayMode = false;
	KEY = false;
	Undo = false;
	Redo = false;
	Sound = false;

	FigTypeClr = 0;
	ClrCount = 0;
	FigCount = 0;
	RecCount = 0;
	RandFigCount = 0;
	Undo_RedoCount = 0;
	Undo_Redo_Count = 0;
	CheckUpdate = false;
	LastActionType = START_PROGRAM;
	srand(time(NULL));
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	for (int i = 0; i < MaxRecCount; i++)
		Recorded[i] = NULL;
	for (int i = 0; i < MaxUndoCount; i++)
		Undo_Redo_List[i] = NULL;

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
		/*if (Undo_Redo_Count == 0)
		{
			pOut->PrintMessage("No Action to undo");
			break;
		}
		if (Undo_RedoCount == 5 && LastActionType == UNDO_ACTION)
		{
			pOut->PrintMessage("Undo Limit Exceeded,Please make another action first");
			break;
		}*/
		pAct = new UndoAction(this);
		break;

	case REDO_ACTION:
		if ((LastActionType != UNDO_ACTION && LastActionType != REDO_ACTION) || Undo_RedoCount == 0)
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
	case DRAG_FIGURE:
		if (SelectedFig == NULL) {
			pOut->PrintMessage("Please Select a Figure First");
			break;
		}
		pAct = new MoveByDragAction(this);
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
		if (LastActionType != START_PROGRAM && LastActionType != CLEAR_ALL) {
			pOut->PrintMessage("You can only record after the program start or after clear all");
			break;
		}
		pAct = new StartRecAction(this);
		RecAction = pAct;
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
	case TO_PLAY:
		pAct = new SwitchToPlayAction(this);
		break;
	case TO_DRAW:
		pAct = new SwitchToDrawAction(this);
		break;
	case PICK_CLR:
		pAct = new PickColors(this);
		break;
	case PICK_TYPE:
		pAct = new PickFigures(this);
		break;
	case PICK_TYPECLR:
		pAct = new PickTypeandColor(this);
		break;
	case SOUND_STATE:
		pAct = new ChangeSoundState(this);
		break;

	case EXIT:
		pAct = new ExitAction(this);
		break;
	}

	if (pAct != NULL)
	{
		LastActionType = ActType;
		CheckUpdate = true;
		bool Delete = pAct->Execute(); //Execute
		if (Delete) delete pAct;
		pAct = NULL;
		if(pAct) LastAction = pAct;
		if (Recording) {
			RecAction->Execute(false);
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
		pFig->SetBlock(false);
	}
}
CFigure* ApplicationManager::GetFigure(Point P1) const
{
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->IsPointInside(P1)) {
			return FigList[i];
		}
	}
	return NULL;
}
void ApplicationManager::DeleteFigure(bool B)
{
	CFigure* save = SelectedFig;
	if (B)
	{
		SelectedFig = FigList[FigCount - 1];
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
	if (B)
	{
		SelectedFig = save;
	}
}
//==============================================================================//
//								Recording functions								//
//==============================================================================//
void ApplicationManager::AddActionRec(Action* Act)
{
	if (RecCount < MaxRecCount)
	{
		Recorded[RecCount++] = Act;
		Act->SetRecorded(true);
	}
}
Action* ApplicationManager::GetLastAction() const
{
	return LastAction;
}
int ApplicationManager::GetUndoRedoCount() const
{
	return Undo_RedoCount;
}
/////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::IsUndo() const{
	return Undo;
}
void ApplicationManager::UndoLastAction()
{
	Undo_RedoCount++;
	Undo_Redo_List[--Undo_Redo_Count]->UndoActions();
}
void ApplicationManager::RedoLastAction()
{
	Undo_RedoCount--;
	Undo_Redo_List[Undo_Redo_Count++]->RedoActions();
}
void ApplicationManager::Add_Undo_Redo_Actions(Action* pAct)
{
	if (Undo_Redo_Count < MaxUndoCount)
	{
		Undo_Redo_List[Undo_Redo_Count++] = pAct;
	}
	else
	{
		if (!Undo_Redo_List[0]->IsRecorded()) {
			delete Undo_Redo_List[0];
		}
		Undo_Redo_List[0] = NULL;
		for (int i = 0; i < Undo_Redo_Count - 1; i++)
		{
			Undo_Redo_List[i] = Undo_Redo_List[i + 1];
		}
		Undo_Redo_List[Undo_Redo_Count - 1] = pAct;
	}
	Undo_RedoCount = 0;
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
			//FigList[i]->ChngClr();
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
	for (int i = 0; i < Undo_Redo_Count; i++)
	{
		if (!Undo_Redo_List[i]->IsRecorded())
			delete Undo_Redo_List[i];
		Undo_Redo_List[i] = NULL;
	}
	if (!PlayingRec) {
		for (int i = 0; i < RecCount; i++)
		{
			delete Recorded[i];
			Recorded[i] = NULL;
		}
		RecCount = 0;
	}
	Undo_RedoCount = 0;
	Undo_Redo_Count = 0;
	FigCount = 0;
	SelectedFig = NULL;
}
CFigure* ApplicationManager::GetSelectedFig()const
{
	return SelectedFig;
}

int ApplicationManager::GetFigCount()const
{
	return FigCount;
}
void ApplicationManager::SetSound(bool sound) {
	Sound = sound;
}
bool ApplicationManager::IsSoundOn() const {
	return Sound;
}
bool ApplicationManager::IsRecording() const {
	return Recording;
}
bool ApplicationManager::IsPlayingRec() const {
	return PlayingRec;
}
bool ApplicationManager::IsPlayMode() const
{
	return PlayMode;
}
void ApplicationManager::SetPlayMode(bool B)
{
	PlayMode = B;
}
void ApplicationManager::SetKEY(bool B)
{
	KEY = B;
}
void ApplicationManager::SetRec(bool IsRec)
{
	Recording = IsRec;
}
void ApplicationManager::SetSelectedFig(CFigure* F)
{
	SelectedFig = F;
}
int ApplicationManager::GetClrCount()const
{
	return ClrCount;
}
void  ApplicationManager::SetClrCount(int C)
{
	ClrCount = C;
}
int ApplicationManager::GetRandFigCount()const
{
	return RandFigCount;
}
void  ApplicationManager::SetRandFigCount(int C)
{
	RandFigCount = C;
}
int ApplicationManager::GetTypeClrCount()const
{
	return FigTypeClr;
}
void  ApplicationManager::SetTypeClrCount(int C)
{
	FigTypeClr = C;
}
shape ApplicationManager::GetRandomFig(int random) {

	if (!FigCount) return noshape;
	if (random == -1) {
		random = rand() % FigCount;
	}
	shape Figtype = FigList[random]->GetFigType();
	for (int i = 0; i < FigCount; i++) {
		if (Figtype == FigList[i]->GetFigType()) {
			if (FigList[random]->getColor() == FigList[i]->getColor()) {
				FigTypeClr++;
			}
			RandFigCount++;
		}
	}
	return Figtype;
}
string ApplicationManager::GetRandomClr(int& random)
{
	if (FigCount == 0) return "NO COLORED FIG";
	random = rand() % FigCount;
	bool Check = false;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->getColor() != "NO FILL CLR")
			Check = true;
	}
	if (!Check) return "NO COLORED FIG";
	while (true)
	{
		if (FigList[random]->getColor() == "NO FILL CLR")
			random = rand() % FigCount;
		else
			break;
	}
	for (int i = 0; i < FigCount; i++)
		if (FigList[random]->getColor() == FigList[i]->getColor())
			ClrCount++;
	return FigList[random]->getColor();
}
void ApplicationManager::UnBlock()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetBlock(false);
	}
}
void ApplicationManager::BlockFig(CFigure* Fig)
{
	Fig->SetBlock(true);
}
void ApplicationManager::PlayRec() {
	PlayingRec = true;
	ClearAll();
	for (int i = 0; i < RecCount; i++) {
		Sleep(1000);

		Recorded[i]->Execute(false);

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
		if (!PlayMode || KEY)
			for (int i = 0; i < FigCount; i++)
			{
				if (!FigList[i]->IsBlocked())
					FigList[i]->Draw(pOut); //Call Draw function (virtual member fn)
			}
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
