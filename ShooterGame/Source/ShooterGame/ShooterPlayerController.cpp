// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShooterGameCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "UIManager.h"
#include "Widget/PopupWidget.h"

void AShooterPlayerController::BeginPlay()
{
    ShooterGameCharacter = Cast<AShooterGameCharacter>(GetPawn());
    InitInputMappingContext();
}

void AShooterPlayerController::InitInputMappingContext()
{
    if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        InputSystem->AddMappingContext(DefaultMappingContext, 0);
        InputSystem->AddMappingContext(CharacterMappingContext, 1);
    }
}

void AShooterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
    {
        if(CharacterMappingContext)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::OnMoveReleased);
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::OnMouseMoved);
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::OnSpacebarReleased);
            EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::OnLeftMouseClicked);
        }

        if(DefaultMappingContext)
        {
            EnhancedInputComponent->BindAction(PopupAction, ETriggerEvent::Started, this, &AShooterPlayerController::OnOpenPopup);
        }
	}
}

void AShooterPlayerController::OnMoveReleased(const FInputActionValue& Value)
{
    if(ShooterGameCharacter)
    {
        ShooterGameCharacter->Move(Value);
    }
}

void AShooterPlayerController::OnSpacebarReleased(const FInputActionValue& Value)
{
    ACharacter* PlayerCharacter = GetCharacter();
    if(PlayerCharacter)
    {
        PlayerCharacter->Jump();
    }
}

void AShooterPlayerController::OnMouseMoved(const FInputActionValue &Value)
{
    if(ShooterGameCharacter)
    {
        ShooterGameCharacter->Look(Value);
    }
}

void AShooterPlayerController::OnLeftMouseClicked(const FInputActionValue& Value)
{
    if(ShooterGameCharacter)
    {
        ShooterGameCharacter->Fire(Value);
    }
}

void AShooterPlayerController::OnOpenPopup(const FInputActionValue& Value)
{
    // check already opened widget
    if(!UUIManager::Instance()->IsWidgetOpened("WBP_BasePopup"))
    {
        FPopupParam Param;
        UPopupWidget* PopupWidget = UUIManager::Instance()->OpenPopup<UPopupWidget>(GetPawn(), "WBP_BasePopup");
        SetUIMode(true);
    }
}

void AShooterPlayerController::SetUIMode(bool bActiveUIMode)
{
    bShowMouseCursor = bActiveUIMode;
    if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if(bActiveUIMode)
        {
            // remove player character input
            FModifyContextOptions Options;
            InputSystem->RemoveMappingContext(CharacterMappingContext, Options);
        }
        else
        {
            InputSystem->AddMappingContext(CharacterMappingContext, 1);
        }
    }
}
