#include "ThiefCatcherGameMode.h"

// /Game/Blueprints/BP_Remy
AThiefCatcherGameMode::AThiefCatcherGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> MainCharacterThiefCatcher(TEXT("/Game/Blueprints/BP_Remy"));
	DefaultPawnClass = MainCharacterThiefCatcher.Class;
}
