#ifndef _LOAD_ACTION_1_H
#define _LOAD_ACTION_1_H

#include <fstream>
#include <string>
#include "Actions/Action.h"
using namespace std;

class ApplicationManager;

// CHANGE 1: Class Name
class LoadAction1 : public Action
{
private:
	string FileName;
public:
	// CHANGE 2: Constructor Name
	LoadAction1(ApplicationManager* pApp);

	// CHANGE 3: Destructor Name
	virtual ~LoadAction1(void);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
#endif