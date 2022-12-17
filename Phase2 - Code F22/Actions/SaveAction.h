#include "Action.h"
#include<fstream>


class SaveAction :public Action
{
	ofstream OutFile;
	string fileName;

public:
	SaveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	string getColor(color);
};
