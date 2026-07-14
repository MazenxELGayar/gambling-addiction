#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

class UMainMenuWidget;

UCLASS()
class NAUGHTYBOT_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UMainMenuWidget> MainMenuWidget;
};
