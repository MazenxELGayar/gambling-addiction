#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFlowBPLibrary.generated.h"

UCLASS()
class NAUGHTYBOT_API UGameFlowBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Show the game over UI instead of quitting. Call this when the last player pawn dies. */
	UFUNCTION(BlueprintCallable, Category = "Game Flow", meta = (WorldContext = "WorldContextObject"))
	static void ShowGameOverScreen(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game Flow", meta = (WorldContext = "WorldContextObject"))
	static void ReturnToMainMenu(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game Flow", meta = (WorldContext = "WorldContextObject"))
	static void RestartGameplayLevel(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game Flow", meta = (WorldContext = "WorldContextObject"))
	static void OpenGameplayLevel(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Game Flow")
	static FName GetMainMenuLevelName();

	UFUNCTION(BlueprintPure, Category = "Game Flow")
	static FName GetGameplayLevelName();
};
