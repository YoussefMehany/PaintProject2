#pragma once
#include "Action.h"
#include<fstream>


class SaveAction :public Action
{
	ofstream OutFile;
	string fileName;

public:
	SaveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual bool Execute(bool ReadParams = true);
	string getColor(color);
	virtual bool CanBeRecorded() const;
	virtual bool CanBeDeleted()  const;
};
