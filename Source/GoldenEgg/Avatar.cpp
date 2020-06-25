// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	PlayerInputComponent->BindAxis("Fly", this, &AAvatar::MoveUp);
	PlayerInputComponent->BindAction("SetFlyMode", IE_Pressed,this, &AAvatar::SetFlyMode);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
}


void AAvatar::MoveForward(float amount)
{
	// Не вводите тело этой функции, если контроллер
	// ещё не установлен или если сумма для движения равна 0
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		// мы вызываем AddMovementInput, чтобы собственно двигать
		// игрока `суммой` в направлениях `fwd`
		AddMovementInput(fwd, amount);
	}
}
void AAvatar::MoveRight(float amount)
{
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::MoveUp(float amount)
{
	
	if (Controller && amount)
	{
		FVector up = GetActorUpVector();
		AddMovementInput(up, amount);
	}
}

void AAvatar::SetFlyMode()
{
	if (!flyMode) 
	{
		GetCharacterMovement()->bCheatFlying = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		flyMode = true;
	}
	else
	{
		GetCharacterMovement()->bCheatFlying = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		flyMode = false;
	}
}

void AAvatar::Pitch(float amount)
{
	AddControllerPitchInput(100.f * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Yaw(float amount)
{
	AddControllerYawInput(100.f * amount * GetWorld()->GetDeltaSeconds());
}