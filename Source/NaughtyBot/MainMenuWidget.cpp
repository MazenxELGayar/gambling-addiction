#include "MainMenuWidget.h"
#include "GameFlowBPLibrary.h"
#include "NaughtyBotGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

TSharedRef<SWidget> UMainMenuWidget::RebuildWidget()
{
	if (!WidgetTree->RootWidget)
	{
		UCanvasPanel* Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
		WidgetTree->RootWidget = Root;

		UBorder* Background = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("Background"));
		Background->SetBrushColor(FLinearColor(0.05f, 0.07f, 0.1f, 1.f));
		UCanvasPanelSlot* BgSlot = Root->AddChildToCanvas(Background);
		BgSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		BgSlot->SetOffsets(FMargin(0.f));

		UVerticalBox* Layout = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("Layout"));
		if (UBorderSlot* BorderSlot = Cast<UBorderSlot>(Background->AddChild(Layout)))
		{
			BorderSlot->SetHorizontalAlignment(HAlign_Center);
			BorderSlot->SetVerticalAlignment(VAlign_Center);
		}

		TitleText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
		TitleText->SetText(FText::FromString(TEXT("NAUGHTY BOT")));
		TitleText->SetJustification(ETextJustify::Center);
		FSlateFontInfo TitleFont = TitleText->GetFont();
		TitleFont.Size = 56;
		TitleText->SetFont(TitleFont);
		TitleText->SetColorAndOpacity(FSlateColor(FLinearColor(0.95f, 0.85f, 0.35f, 1.f)));
		if (UVerticalBoxSlot* TitleSlot = Layout->AddChildToVerticalBox(TitleText))
		{
			TitleSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 40.f));
			TitleSlot->SetHorizontalAlignment(HAlign_Center);
		}

		PlayButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("PlayButton"));
		UTextBlock* PlayLabel = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("PlayLabel"));
		PlayLabel->SetText(FText::FromString(TEXT("Play")));
		PlayLabel->SetJustification(ETextJustify::Center);
		FSlateFontInfo ButtonFont = PlayLabel->GetFont();
		ButtonFont.Size = 24;
		PlayLabel->SetFont(ButtonFont);
		PlayButton->AddChild(PlayLabel);
		if (UVerticalBoxSlot* PlaySlot = Layout->AddChildToVerticalBox(PlayButton))
		{
			PlaySlot->SetPadding(FMargin(0.f, 0.f, 0.f, 12.f));
			PlaySlot->SetHorizontalAlignment(HAlign_Center);
		}

		QuitButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("QuitButton"));
		UTextBlock* QuitLabel = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("QuitLabel"));
		QuitLabel->SetText(FText::FromString(TEXT("Quit")));
		QuitLabel->SetJustification(ETextJustify::Center);
		QuitLabel->SetFont(ButtonFont);
		QuitButton->AddChild(QuitLabel);
		if (UVerticalBoxSlot* QuitSlot = Layout->AddChildToVerticalBox(QuitButton))
		{
			QuitSlot->SetHorizontalAlignment(HAlign_Center);
		}
	}

	return Super::RebuildWidget();
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}

	SetupInputMode();
}

void UMainMenuWidget::SetupInputMode() const
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	UGameFlowBPLibrary::OpenGameplayLevel(this);
}

void UMainMenuWidget::OnQuitClicked()
{
	if (UNaughtyBotGameInstance* GI = GetGameInstance<UNaughtyBotGameInstance>())
	{
		GI->RequestRealQuit();
		return;
	}

	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
}
