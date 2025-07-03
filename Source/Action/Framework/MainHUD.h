// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Action/UI/MainWidget.h"
#include "Action/UI/Clear/UserWidget_ClearPanel.h"
#include "MainHUD.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPostBeginPlay);

/**
 * 
 */
UCLASS()
class ACTION_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	inline void OpenShop() { if (MainWidget) MainWidget->ShowShop(true); };
	inline void ToggleInventory() { if (MainWidget) MainWidget->ToggleInventory(); };
	inline FOnInventoryOpen& GetInventoryOpenDelegate() { return MainWidget->GetInventoryOpenDelegate(); };
	FOnPostBeginPlay OnPostBeginPlay;

	UFUNCTION(BlueprintCallable, Category = "GameClear")
	void GameClear();

	UFUNCTION(BlueprintCallable, Category = "GameClear")
	inline void RefreshRankList() { if (ClearWidget) ClearWidget->RefreshRankList(); };

	UFUNCTION(BlueprintCallable, Category = "GameClear")
	inline void OnNewRanker(int32 InRank) { if (ClearWidget) ClearWidget->OnNewRanker(InRank); };
	

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	inline UMainWidget* GetMainWidget() const { return MainWidget; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY()
	UMainWidget* MainWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clear")
	TSubclassOf<UUserWidget_ClearPanel> ClearWidgetClass;

	UPROPERTY()
	UUserWidget_ClearPanel* ClearWidget = nullptr;
};
