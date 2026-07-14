#include "MainMenuGameMode.h"
#include "MainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	// No pawn on the menu level — UI only.
	DefaultPawnClass = nullptr;
	HudClass = nullptr;
	PlayerControllerClass = APlayerController::StaticClass();
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		return;
	}

	MainMenuWidget = CreateWidget<UMainMenuWidget>(PC, UMainMenuWidget::StaticClass());
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport(0);
	}
}
