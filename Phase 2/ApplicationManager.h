#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include <fstream> // Make sure this is at the top!

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
public:	
	ApplicationManager(); //constructor
	bool IsAreaOccupied(GraphicsInfo newGate);
	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	// Saves all components to the provided file
	void SaveAll(ofstream& outputfile);

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	// Loads all components from the provided file
	void LoadAll(ifstream& inputfile);
	Component* GetComponent(int x, int y);
	
	// Get component list access for actions
	int GetComponentCount() const { return CompCount; }
	Component* GetComponentByIndex(int index) const;

	// Toggle switch at given coordinates if it exists
	bool ToggleSwitch(int x, int y);
	void UpdateSimulation();//for connection 
	//destructor
	~ApplicationManager();
};

#endif