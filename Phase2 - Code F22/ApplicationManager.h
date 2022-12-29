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
	enum { MaxRecCount = 20, MaxFigCount = 200, MaxUndoCount = 5};	//Max number for arrays

private:
	int FigCount; //Actual number of figures
	int RecCount;	//Actual number of recordings
	int Undo_RedoLimit; //Number of consecutive undo_redo actions
	int Undo_Redo_Count; //Actual number of undo_redo
	int ClrCount; //number of occurences of a certain color
	int RandFigCount; //number of occurences of a certain figure
	int FigTypeClr; //number of occurences of a figure with a certain color
	bool Recording; //recording state
	bool PlayingRec; //playing recording state
	bool PlayMode; //indicates if the current mode is play mode
	bool KEY; //allows us to access the figures after clicking on the play icon
	bool Undo; //Undo state
	bool Redo; //Redo state
	bool Sound; //Sound state
	

	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* SelectedFig; //Pointer to the selected figure


	Action* Undo_Redo_List[MaxUndoCount]; //List of all undo_redo actions
	Action* Recorded[MaxRecCount]; //List of all recordings
	Action* LastAction; //Last Action
	Action* RecAction; //to access the recording class object

	//Pointers to Input and Output classes

	Input *pIn; //input
	Output *pOut; //output

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	Action* GetLastAction() const; //Returns the LastAction
	void ExecuteAction(ActionType); //Creates an action and executes it

	// -- Figures Management Functions

	CFigure *GetFigure(Point P1) const;//Search for a figure given a point inside the figure
	CFigure* GetSelectedFig()const; //Returns the selectedfig pointer

	void AddFigure(CFigure* pFig);   //Adds a new figure to the FigList
	void SetSelectedFig(CFigure*); //Sets the selectedfig pointer
	void ClearAll(); //Clears all the lists and resets the class
	void DeleteFigure(CFigure* B = NULL); //Deletes a Figure
	int GetFigCount()const; //Returns the figures count
	bool IsSoundOn() const; //Returns sound state

	// -- Sound
	
	void SetSound(bool sound); //Sets sound state

	// -- Recording

	void AddActionRec(Action*); //Adds an action to the recording list
	void SetRec(bool IsRec); //Set Recording state
	void PlayRec(); //Plays the recordings
	bool IsRecording() const; //Returns the recording state
	bool IsPlayingRec() const; //Returns the playing state
	int GetRecCount() const; //Returns the record count

	// -- Save-Load

	void SaveFile(ofstream& OutFile); //Saves a file

	// -- Undo-Redo

	CFigure* GetLastAdd();	//Returns the last drawn figure based on the greatest ID
	void UndoLastAction(); //Undoes the last action
	void RedoLastAction(); //Redoes the last action
	void SwapFigures(CFigure*);	//Swaps two figures based on ID
	void Add_Undo_Redo_Actions(Action*); //Adds Actions to UndoRedo list
	bool IsUndo() const; //Returns Undo state
	bool IsRedo() const; //Returns Redo state
	int GetUndoRedoCount() const; //Returns Undo count
	int GetUndoRedoLimit() const; //Returns Redo count

	// --Play Mode

	string GetRandomClr(int&); //Returns Random color to the playmode
	shape GetRandomFig(int); //Returns Random figure to the playmode
	void SetPlayMode(bool); //Sets current mode to play mode
	void SetKEY(bool); //Sets the Key
	void UnBlock(); //Unblocks a figure to be drawn again
	void BlockFig(CFigure*); //Blocks a figure not to be drawn
	void SetClrCount(int); //Sets the number of occurences of a certain color
	void SetRandFigCount(int);	//Sets the number of occurences of a certain figure
	void SetTypeClrCount(int); //Sets the number of occurences of a figure with a certain color
	bool IsPlayMode()const; //Returns whether the current mode is play mode
	bool IsColored(); //Returns the color state
	int GetClrCount(int); //Returns the number of occurences of a certain color
	int GetRandFigCount()const; //Returns the number of occurences of a certain figure
	int GetTypeClrCount()const; //Returns the number of occurences of a figure with a certain color

	// -- Interface Management Functions

	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface();	//Redraws all the drawing window	
};

#endif