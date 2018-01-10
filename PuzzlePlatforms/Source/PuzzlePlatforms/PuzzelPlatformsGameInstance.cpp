// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzelPlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"

UPuzzelPlatformsGameInstance::UPuzzelPlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;
}

void UPuzzelPlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class: %s"), *MenuClass->GetName());
}

void UPuzzelPlatformsGameInstance::BeginPlay()
{
	LoadMenu();
}

void UPuzzelPlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;
	Menu->AddToViewport();
}

void UPuzzelPlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzelPlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
