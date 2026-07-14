#include "GameOverWidget.h"
#include "GameFlowBPLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "GameFramework/PlayerController.h"

TSharedRef<SWidget> UGameOverWidget::RebuildWidget()
{
	if (!WidgetTree->RootWidget)
	{
		UCanvasPanel* Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
		WidgetTree->RootWidget = Root;

		UBorder* Dimmer = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("Dimmer"));
		Dimmer->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.72f));
		UCanvasPanelSlot* DimmerSlot = Root->AddChildToCanvas(Dimmer);
		DimmerSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		DimmerSlot->SetOffsets(FMargin(0.f));

		UVerticalBox* Layout = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("Layout"));
		if (UBorderSlot* BorderSlot = Cast<UBorderSlot>(Dimmer->AddChild(Layout)))
		{
			BorderSlot->SetHorizontalAlignment(HAlign_Center);
			BorderSlot->SetVerticalAlignment(VAlign_Center);
		}

		TitleText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
		TitleText->SetText(FText::FromString(TEXT("GAME OVER")));
		TitleText->SetJustification(ETextJustify::Center);
		FSlateFontInfo TitleFont = TitleText->GetFont();
		TitleFont.Size = 48;
		TitleText->SetFont(TitleFont);
		TitleText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		if (UVerticalBoxSlot* TitleSlot = Layout->AddChildToVerticalBox(TitleText))
		{
			TitleSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 32.f));
			TitleSlot->SetHorizontalAlignment(HAlign_Center);
		}

		RestartButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("RestartButton"));
		UTextBlock* RestartLabel = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("RestartLabel"));
		RestartLabel->SetText(FText::FromString(TEXT("Restart")));
		RestartLabel->SetJustification(ETextJustify::Center);
		FSlateFontInfo ButtonFont = RestartLabel->GetFont();
		ButtonFont.Size = 22;
		RestartLabel->SetFont(ButtonFont);
		RestartButton->AddChild(RestartLabel);
		if (UVerticalBoxSlot* RestartSlot = Layout->AddChildToVerticalBox(RestartButton))
		{
			RestartSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 12.f));
			RestartSlot->SetHorizontalAlignment(HAlign_Center);
			RestartSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		}

		MainMenuButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("MainMenuButton"));
		UTextBlock* MenuLabel = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("MainMenuLabel"));
		MenuLabel->SetText(FText::FromString(TEXT("Quit to Main Menu")));
		MenuLabel->SetJustification(ETextJustify::Center);
		MenuLabel->SetFont(ButtonFont);
		MainMenuButton->AddChild(MenuLabel);
		if (UVerticalBoxSlot* MenuSlot = Layout->AddChildToVerticalBox(MainMenuButton))
		{
			MenuSlot->SetHorizontalAlignment(HAlign_Center);
		}
	}

	return Super::RebuildWidget();
}

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartClicked);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMainMenuClicked);
	}

	SetupInputMode();
}

void UGameOverWidget::SetupInputMode() const
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void UGameOverWidget::OnRestartClicked()
{
	UGameFlowBPLibrary::RestartGameplayLevel(this);
}

void UGameOverWidget::OnMainMenuClicked()
{
	UGameFlowBPLibrary::ReturnToMainMenu(this);
}
