#include "Action.h"
#include<fstream>


class AddSaveAction :public Action
{
	ofstream OutFile;
	string fileName;

public:
	AddSaveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	string getColor(color);
};
