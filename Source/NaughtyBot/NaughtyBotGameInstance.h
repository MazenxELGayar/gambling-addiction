#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NaughtyBotGameInstance.generated.h"

UCLASS()
class NAUGHTYBOT_API UNaughtyBotGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	/** Used by main menu Quit so we perform a real exit instead of Game Over. */
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void RequestRealQuit();

private:
	void RegisterQuitOverride();
	void UnregisterQuitOverride();

	void HandleQuitCommand();

	bool bAllowRealQuit = false;
	bool bQuitOverrideRegistered = false;
};
