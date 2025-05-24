// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDWidget.generated.h"

class UListView;

/**
 * 
 */
UCLASS()
class UNREALWORLD_API UInGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	void BP_OnClicked_TriggerButton();

protected:
	UPROPERTY(meta=(BindWidgetOptional))
	UListView* SimpleListView;

	UPROPERTY(EditDefaultsOnly)
	int32 ItemWidgetNumForTest = 5;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> TableViewItemWidget;
};
