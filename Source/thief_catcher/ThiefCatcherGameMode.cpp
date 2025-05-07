#include "ThiefCatcherGameMode.h"
#include "CharacterHUD.h"

AThiefCatcherGameMode::AThiefCatcherGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> MainCharacterThiefCatcher(TEXT("/Game/Remy/BP_Remy"));
	DefaultPawnClass = MainCharacterThiefCatcher.Class;
	HUDClass = ACharacterHUD::StaticClass();
}