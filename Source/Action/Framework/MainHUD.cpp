// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "Blueprint/UserWidget.h"
#include "Action/player/ActionPlayerController.h"


void AMainHUD::GameClear()
{
	if (ClearWidgetClass)
	{
		MainWidget->RemoveFromParent();

		ClearWidget = CreateWidget<UUserWidget_ClearPanel>(GetWorld(), ClearWidgetClass);
		if (ClearWidget)
		{
			ClearWidget->AddToViewport();
		}
	}
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (MainWidgetClass)
	{
		UWorld* World = GetWorld();

		MainWidget = CreateWidget<UMainWidget>(World, MainWidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();			
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AMainHUD::BeginPlay() called"));	// 디버그 메시지 출력
	//OnPostBeginPlay.Broadcast();

	AActionPlayerController* MyPlayerController = Cast<AActionPlayerController>(GetWorld()->GetFirstPlayerController());
	if (MyPlayerController)
	{
		FOnInventoryOpen& InventoryOpenDelegate = MainWidget->GetInventoryOpenDelegate();
		InventoryOpenDelegate.AddUObject(MyPlayerController, &AActionPlayerController::OnInventoryOpen);
	}
}