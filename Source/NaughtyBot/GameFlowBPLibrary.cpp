#include "GameFlowBPLibrary.h"
#include "GameOverWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

namespace NaughtyBotGameFlow
{
	static const FName MainMenuLevel(TEXT("Lvl_MainMenu"));
	static const FName GameplayLevel(TEXT("NaughtMap"));
}

FName UGameFlowBPLibrary::GetMainMenuLevelName()
{
	return NaughtyBotGameFlow::MainMenuLevel;
}

FName UGameFlowBPLibrary::GetGameplayLevelName()
{
	return NaughtyBotGameFlow::GameplayLevel;
}

void UGameFlowBPLibrary::ShowGameOverScreen(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return;
	}

	UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr;
	if (!World)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		return;
	}

	TArray<UUserWidget*> Found;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, Found, UGameOverWidget::StaticClass(), false);
	if (Found.Num() > 0)
	{
		return;
	}

	UGameOverWidget* GameOver = CreateWidget<UGameOverWidget>(PC, UGameOverWidget::StaticClass());
	if (!GameOver)
	{
		return;
	}

	GameOver->AddToViewport(100);
	UGameplayStatics::SetGamePaused(World, true);
}

void UGameFlowBPLibrary::ReturnToMainMenu(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return;
	}

	UGameplayStatics::SetGamePaused(WorldContextObject, false);
	UGameplayStatics::OpenLevel(WorldContextObject, NaughtyBotGameFlow::MainMenuLevel);
}

void UGameFlowBPLibrary::RestartGameplayLevel(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return;
	}

	UGameplayStatics::SetGamePaused(WorldContextObject, false);
	UGameplayStatics::OpenLevel(WorldContextObject, NaughtyBotGameFlow::GameplayLevel);
}

void UGameFlowBPLibrary::OpenGameplayLevel(const UObject* WorldContextObject)
{
	RestartGameplayLevel(WorldContextObject);
}
