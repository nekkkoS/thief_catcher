#include "ThiefCatcherGameMode.h"
#include "../CharacterHUD/CharacterHUD.h"

AThiefCatcherGameMode::AThiefCatcherGameMode() : Super()
{
	const ConstructorHelpers::FClassFinder<APawn> MainCharacterThiefCatcher(TEXT("/Game/Remy/BP_Remy"));
	DefaultPawnClass = MainCharacterThiefCatcher.Class;
	HUDClass = ACharacterHUD::StaticClass();
}
