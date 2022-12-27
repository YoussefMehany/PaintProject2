#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Actions/Action.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxRecCount = 20, MaxFigCount = 200, MaxUndoCount = 5};	//Max no for arrays

private:
	int FigCount; //Actual number of figures
	int RecCount;
	int Undo_RedoCount;
	int ListCounter_Undo_Redo;
	int ActionCount;
	int ClrCount;
	int RandFigCount;
	bool CheckUpdate;
	bool Recording;
	bool PlayingRec;
	bool PlayMode;
	bool KEY;
	bool Undo;
	bool Redo;
	bool Sound;
	ActionType LastAction;
	

	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* SelectedFig; //Pointer to the selected figure


	Action* SaveUndo_RedoActions[MaxUndoCount]; //saves figures before being changed 
	Action* Recorded[MaxRecCount];
	
	//Pointers to Input and Output classes

	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	CFigure *GetFigure(Point P1) const;//Search for a figure given a point inside the figure
	void AddFigure(CFigure* pFig);   //Adds a new figure to the FigList
	void MoveFigure(Point P1);
	bool IsRecording() const;
	bool IsPlayingRec() const;
	void SetRec(bool IsRec);
	void SetSelectedFig(CFigure*);
	CFigure* GetSelectedFig()const;
	void PlayRec();
	int getFigCount()const;
	void DeleteFigure(CFigure*F=NULL);
	void SaveFile(ofstream& OutFile);
	void SetSound(bool sound);
	bool IsSoundOn() const;
	void ClearAll();
	// -- Undo-Redo
	void UndoLastAction();
	void RedoLastAction();
	void DeleteLastFig();
	void SwapFigures(CFigure*);
	void Add_Undo_Redo_Actions(Action*);
	// --Play Mode_
	bool IsPlayMode()const;
	void SetPlayMode(bool);
	void SetKEY(bool);
	string GetRandomClr();
	shape GetRandomFig();
	void UnBlock();
	void BlockFig(CFigure*);
	int GetClrCount()const;
	void SetClrCount(int );
	int GetRandFigCount()const;
	void SetRandFigCount(int);
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface();	//Redraws all the drawing window	
};

#endif