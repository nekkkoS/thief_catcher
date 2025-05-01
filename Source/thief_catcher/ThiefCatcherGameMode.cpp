#include "ThiefCatcherGameMode.h"

AThiefCatcherGameMode::AThiefCatcherGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> MainCharacterThiefCatcher(TEXT("/Game/Blueprints/BP_Remy"));
	DefaultPawnClass = MainCharacterThiefCatcher.Class;
}
