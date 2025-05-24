// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUDWidget.h"
#include "Runtime/UMG/Public/Components/ListView.h"

void UInGameHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInGameHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	 
	TArray<UUserWidget*> Widgets;
	for (int32 Idx = 0; Idx < ItemWidgetNumForTest; ++Idx)
	{
		if (UUserWidget* CreatedItemWidget = CreateWidget(this, TableViewItemWidget.Get()))
		{
			Widgets.Add(CreatedItemWidget);
		}
	}

	SimpleListView->SetListItems(Widgets);
	
}

void UInGameHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInGameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInGameHUDWidget::BP_OnClicked_TriggerButton()
{
	UE_LOG(LogTemp, Log, TEXT("UInGameHUDWidget::BP_OnClicked_TriggerButton()"));
}
