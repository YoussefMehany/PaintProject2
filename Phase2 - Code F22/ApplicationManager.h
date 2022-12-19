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
	enum { MaxRecCount = 200, MaxFigCount = 200, MaxUndoCount = 500};	//Max no for arrays

private:
	int FigCount; //Actual number of figures
	int RecCount;
	int UndoCount;
	int ListCounter;
	int ActionCounter;
	int FigTurn;
	bool CheckUpdate;
	bool Recording;
	bool PlayingRec;
	ActionType LastActions[MaxUndoCount];
	CFigure* SelectedFigs[MaxUndoCount];
    CFigure* UndoFigList[MaxUndoCount];
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	ActionType LastAction;
	CFigure* SelectedFig; //Pointer to the selected figure
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
	CFigure* GetAddress(int id);
	void PrintLastMsg();
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(Point P1) const; //Search for a figure given a point inside the figure
	void MoveFigure(Point P1);
	void SelectFigure(Point P1);
	void ChangeColor(color clr);
	bool IsRecording() const;
	bool IsPlayingRec() const;
	void SetRec(bool IsRec);
	void PlayRec();
	int getFigCount()const;
	void DeleteFigure();
	void SaveFile(ofstream& OutFile);
	void UndoLastAction(ActionType Act);
	void ClearAll();
	void SetLastAction(ActionType Act);
	ActionType getLastAction()const;
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface();	//Redraws all the drawing window	
};

#endif