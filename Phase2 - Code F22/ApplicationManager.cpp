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
#include "Actions\MoveByDragAction.h"
#include "Actions\ExitAction.h"
#include "Actions\SwitchToDrawAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\PickColors.h"
#include "Actions\PickFigures.h"
#include "Actions\PickTypeandColor.h"
#include "Actions\ChangeSoundState.h"
#include "Actions\ResizeAction.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	//Initialize the data members

	SelectedFig = NULL;
	RecAction = NULL;

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
	Undo_RedoLimit = 0;
	Undo_Redo_Count = 0;

	srand(time(NULL)); //starts the seed time with zero

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
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	//According to Action Type, create the corresponding action object
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
		pAct = new UndoAction(this);
		break;
	case REDO_ACTION:
		pAct = new RedoAction(this);
		break;
	case MOVE_FIGURE:
		pAct = new MoveAction(this);
		break;
	case DRAG_FIGURE:
		pAct = new MoveByDragAction(this);
		break;
	case RESIZE_FIGURE:
		pAct = new ResizeAction(this);
		break;
	case SELECT_FIGURE:
		pAct = new SelectAction(this);
		break;
	case GREENCLR:
		pAct = new ChangeColorAction(this, GREEN);
		break;
	case REDCLR:
		pAct = new ChangeColorAction(this, RED);
		break;
	case BLUECLR:
		pAct = new ChangeColorAction(this, BLUE);
		break;
	case ORANGECLR:
		pAct = new ChangeColorAction(this, ORANGE);
		break;
	case YELLOWCLR:
		pAct = new ChangeColorAction(this, YELLOW);
		break;
	case BLACKCLR:
		pAct = new ChangeColorAction(this, BLACK);
		break;
	case DELETE_FIGURE:
		pAct = new DeleteAction(this);
		break;
	case SAVE_PROGRESS:
		pAct = new SaveAction(this);
		break;
	case LOAD_PROGRESS:
		pAct = new LoadAction(this);
		break;
	case START_REC:
		pAct = new StartRecAction(this);
		RecAction = pAct;
		break;
	case STOP_REC:
		pAct = new StopRecAction(this);
		break;
	case PLAY_REC:
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
	case STATUS:
		return;
	case EXIT:
		pAct = new ExitAction(this);
		break;
	}

	if (pAct != NULL)
	{
		bool Delete = pAct->Execute(); //Execute
		LastAction = pAct;
		if (Recording)
		{
			RecAction->Execute(false);
		}
		if (Delete)
		{
			delete pAct;
			pAct = NULL;
		}
	}
}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
	{
		FigList[FigCount++] = pFig;
		pFig->SetBlock(false);
	}
}
CFigure* ApplicationManager::GetLastAdd()
{
	if (FigCount > 0)
	{
		int max = 0, index = 0;
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i]->GetID() > max)
			{
				max = FigList[i]->GetID();
				index = i;
			}
		}
		return FigList[index];
	}
	return NULL;
}
void ApplicationManager::SwapFigures(CFigure* F)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID() == F->GetID())
		{
			if (FigList[i]->IsSelected())
			{
				FigList[i]->SetSelected(false);
				F->SetSelected(true);
				SetSelectedFig(F);
			}
			else
				F->SetSelected(false);
			delete FigList[i];
			FigList[i] = F;
			break;
		}
	}
}
CFigure* ApplicationManager::GetFigure(Point P1) const
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsPointInside(P1))
		{
			return FigList[i];
		}
	}
	return NULL;
}
void ApplicationManager::DeleteFigure(CFigure* B)
{
	CFigure* save = SelectedFig;
	if (Undo || Redo)
		SelectedFig = B;
	if (FigCount > 0)
	{
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i]->GetID() == SelectedFig->GetID())
			{
				delete FigList[i];
				for (int j = i; j < FigCount - 1; j++) //Shifts each pointer to point at the figure of its next element
				{
					FigList[j] = FigList[j + 1];
				}
				SelectedFig = NULL;
				FigList[--FigCount] = NULL;
				break;
			}
		}
		if (Undo || Redo)
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
void ApplicationManager::PlayRec()
{
	for (int i = 0; i < RecCount; i++)
	{
		Sleep(1000);
		Recorded[i]->Execute(false);
		UpdateInterface();
	}
}

//==============================================================================//
//								Undo and Redo Functions							//
//==============================================================================//

bool ApplicationManager::IsUndo() const {
	return Undo;
}
bool ApplicationManager::IsRedo() const
{
	return Redo;
}
void ApplicationManager::UndoLastAction()
{
	Undo = true;
	Undo_RedoLimit++;
	Undo_Redo_List[--Undo_Redo_Count]->UndoActions();
}
void ApplicationManager::RedoLastAction()
{
	Redo = true;
	Undo_RedoLimit--;
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
		if (!Undo_Redo_List[0]->IsRecorded())
		{
			delete Undo_Redo_List[0];
		}
		Undo_Redo_List[0] = NULL;
		for (int i = 0; i < Undo_Redo_Count - 1; i++)
		{
			Undo_Redo_List[i] = Undo_Redo_List[i + 1];
		}
		Undo_Redo_List[Undo_Redo_Count - 1] = pAct;
	}
	Undo = Redo = false;
	Undo_RedoLimit = 0;
}

void ApplicationManager::ClearAll()
{
	UI.IsFilled = false;
	UI.DrawColor = BLUE;    //Drawing color
	UI.FillColor = GREEN;    //Filling color
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	for (int i = 0; i < Undo_Redo_Count; i++)
	{
		Undo_Redo_List[i]->ClearSaved();
		if (!Undo_Redo_List[i]->IsRecorded())
			delete Undo_Redo_List[i];
		Undo_Redo_List[i] = NULL;
	}
	if (!PlayingRec)
	{
		for (int i = 0; i < RecCount; i++)
		{
			delete Recorded[i];
			Recorded[i] = NULL;
		}
		if (RecAction)
			delete RecAction;
		RecAction = NULL;
		RecCount = 0;
	}
	Undo_RedoLimit = 0;
	Undo_Redo_Count = 0;
	FigCount = 0;
	SelectedFig = NULL;
}
/////////////////////////////////////////////////////////////////////////////////
//==============================================================================//
//								Setters and getters   						    //
//==============================================================================//

CFigure* ApplicationManager::GetSelectedFig()const
{
	return SelectedFig;
}
Action* ApplicationManager::GetLastAction() const
{
	return LastAction;
}
int ApplicationManager::GetRandFigCount()const
{
	return RandFigCount;
}
int ApplicationManager::GetUndoRedoCount() const
{
	return Undo_Redo_Count;
}
int ApplicationManager::GetUndoRedoLimit() const
{
	return Undo_RedoLimit;
}
int ApplicationManager::GetTypeClrCount()const
{
	return FigTypeClr;
}
int ApplicationManager::GetFigCount()const
{
	return FigCount;
}
int ApplicationManager::GetRecCount()const
{
	return RecCount;
}
int ApplicationManager::GetClrCount(int random)
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[random]->getColor() == FigList[i]->getColor())
			ClrCount++;
	return ClrCount;
}
bool ApplicationManager::IsSoundOn() const
{
	return Sound;
}
bool ApplicationManager::IsRecording() const
{
	return Recording;
}
bool ApplicationManager::IsPlayingRec() const
{
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
void ApplicationManager::SetPlayingRec(bool B)
{
	PlayingRec = B;
}
void ApplicationManager::SetSound(bool sound)
{
	Sound = sound;
}
void  ApplicationManager::SetRandFigCount(int C)
{
	RandFigCount = C;
}
void ApplicationManager::SetSelectedFig(CFigure* F)
{
	SelectedFig = F;
}
void  ApplicationManager::SetClrCount(int C)
{
	ClrCount = C;
}
void  ApplicationManager::SetTypeClrCount(int C)
{
	FigTypeClr = C;
}
/////////////////////////////////////////////////////////////////////////////////
//==============================================================================//
//								Play Mode Functions   						    //
//==============================================================================//

shape ApplicationManager::GetRandomFig(int random)
{

	if (!FigCount) return noshape;
	shape Figtype = FigList[random]->GetFigType();
	for (int i = 0; i < FigCount; i++)
	{
		if (Figtype == FigList[i]->GetFigType())
		{
			if (FigList[random]->getColor() == FigList[i]->getColor())
			{
				FigTypeClr++;
			}
			RandFigCount++;
		}
	}
	return Figtype;
}
string ApplicationManager::GetRandomClr(int& random)
{
	if (!IsColored() || FigCount == 0)  return "NO COLORED FIG";
	while (true)
	{
		if (FigList[random]->getColor() == "NO FILL CLR")
			random = rand() % FigCount;
		else
			break;
	}
	return FigList[random]->getColor();
}
bool ApplicationManager::IsColored()
{
	bool Check = false;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->getColor() != "NO FILL CLR")
			Check = true;
	}
	if (!Check) return false;
	return true;
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
	pOut->ClearDrawArea();
	if (!PlayMode || KEY)
		for (int i = 0; i < FigCount; i++)
		{
			if (!FigList[i]->IsBlocked())
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
	delete pIn;
	delete pOut;
}
