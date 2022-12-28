#include "ChangeSoundState.h"

ChangeSoundState::ChangeSoundState(ApplicationManager* pApp) :Action(pApp)
{

}
//Reads parameters required for action to execute (code depends on action type)
void ChangeSoundState::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    if (pManager->IsSoundOn()) {
        pOut->PrintMessage("Sound disabled");
    }
    else {
        pOut->PrintMessage("Sound enabled");
    }
}

//Execute action (code depends on action type)
void ChangeSoundState::Execute(bool ReadParams)
{
    if (ReadParams) {
        ReadActionParameters();
    }
    pManager->SetSound(!pManager->IsSoundOn());
}
bool ChangeSoundState::CanBeRecorded() const
{
    return true;
}