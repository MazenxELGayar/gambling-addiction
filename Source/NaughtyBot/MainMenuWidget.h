#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class NAUGHTYBOT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY()
	TObjectPtr<UButton> PlayButton;

	UPROPERTY()
	TObjectPtr<UButton> QuitButton;

	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnQuitClicked();

	void SetupInputMode() const;
};
