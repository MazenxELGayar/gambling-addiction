#include "NaughtyBotGameInstance.h"
#include "GameFlowBPLibrary.h"
#include "HAL/IConsoleManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Misc/CoreDelegates.h"

void UNaughtyBotGameInstance::Init()
{
	Super::Init();
	RegisterQuitOverride();
}

void UNaughtyBotGameInstance::Shutdown()
{
	UnregisterQuitOverride();
	Super::Shutdown();
}

void UNaughtyBotGameInstance::RequestRealQuit()
{
	bAllowRealQuit = true;
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
	bAllowRealQuit = false;
}

void UNaughtyBotGameInstance::RegisterQuitOverride()
{
	if (bQuitOverrideRegistered)
	{
		return;
	}

	// Replace engine "quit" so last-pawn Blueprint Quit Game shows Game Over instead of exiting.
	IConsoleManager& ConsoleManager = IConsoleManager::Get();
	ConsoleManager.UnregisterConsoleObject(TEXT("quit"), /*bKeepState=*/false);
	ConsoleManager.RegisterConsoleCommand(
		TEXT("quit"),
		TEXT("NaughtyBot: show Game Over during gameplay; exit from main menu / forced quit."),
		FConsoleCommandDelegate::CreateUObject(this, &UNaughtyBotGameInstance::HandleQuitCommand),
		ECVF_Default);

	bQuitOverrideRegistered = true;
}

void UNaughtyBotGameInstance::UnregisterQuitOverride()
{
	if (!bQuitOverrideRegistered)
	{
		return;
	}

	IConsoleManager& ConsoleManager = IConsoleManager::Get();
	ConsoleManager.UnregisterConsoleObject(TEXT("quit"), false);

	// Restore a simple exit command for editor/session cleanup after our module unloads.
	ConsoleManager.RegisterConsoleCommand(
		TEXT("quit"),
		TEXT("Exit the game."),
		FConsoleCommandDelegate::CreateLambda([]()
		{
			FPlatformMisc::RequestExit(false);
		}),
		ECVF_Default);

	bQuitOverrideRegistered = false;
}

void UNaughtyBotGameInstance::HandleQuitCommand()
{
	if (bAllowRealQuit)
	{
		FPlatformMisc::RequestExit(false);
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		FPlatformMisc::RequestExit(false);
		return;
	}

	const FString MapName = UGameplayStatics::GetCurrentLevelName(World, true);

	if (MapName.Equals(TEXT("Lvl_MainMenu"), ESearchCase::IgnoreCase))
	{
		FPlatformMisc::RequestExit(false);
		return;
	}

	// Gameplay (and any other play map): show Game Over instead of quitting.
	UGameFlowBPLibrary::ShowGameOverScreen(World);
}
