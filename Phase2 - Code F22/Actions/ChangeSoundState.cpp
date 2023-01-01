#include "ChangeSoundState.h"
ChangeSoundState::ChangeSoundState(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ChangeSoundState::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    UI.Sound = !UI.Sound;
    pOut->CreateDrawToolBar();
    if (UI.Sound) 
    {
        pOut->PrintMessage("Sound enabled");
    }
    else 
    {
        pOut->PrintMessage("Sound disabled");
    }
}

//Execute action (code depends on action type)
bool ChangeSoundState::Execute(bool ReadParams)
{
    if (ReadParams) 
    {
        ReadActionParameters();
    }
    return true;
}
bool ChangeSoundState::CanBeRecorded() const
{
    return true;
}