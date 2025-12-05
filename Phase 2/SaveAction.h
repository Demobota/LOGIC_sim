#ifndef _SAVE_ACTION_H
#define _SAVE_ACTION_H

#include "..\Phase 2\Actions\Action.h"
#include <fstream>
#include "Components\Connection.h"
#include <string> // Added this
using namespace std; // Added this so "string" is recognized
//rebalsherif "the whole savefile class and all its content"
class SaveAction : public Action
{
private:
	string FileName;
public:
	SaveAction(ApplicationManager* pApp);
	virtual ~SaveAction(void);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
#endif