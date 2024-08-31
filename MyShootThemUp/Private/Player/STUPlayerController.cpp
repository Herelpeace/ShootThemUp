// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerController.cpp


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


ASTUPlayerController::ASTUPlayerController()
{
	// ������� ��� ��������� RespawnComponent
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespwnComponent");
}


void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ������������� �� ������� OnMatchStateChanged
	if (GetWorld())
	{
		// �������� ������� GameMode
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			// ������������� �� ������� ��������� ���� OnMatchStateChanged
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
			// ����� ���������� ������� OnMatchStateChanged
		}
	}

}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);

}

// ������� � ������� ���������� ������� input ������
void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// ��������� ��������� InputComponent
	if (!InputComponent) return;

	// ������ ������ ����� �� ������� OnPauseGame
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
}


// Callback ������� ��� SetupInputComponent()
void ASTUPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	// �������� ������� ����� ������� �������������� � GameMode
	GetWorld()->GetAuthGameMode()->SetPause(this);

}


// Callback �������, ������� ����������� �� ������� ��������� ��������� ���� � BeginPlay, OnMatchStateChanged
// ���������� ������ ��� ����� �������� ��������� ���� 
void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		// ������� ������ ����
		// ��� �� ������ �������������� ���� ��� ������� �������
		SetInputMode(FInputModeGameOnly());

		// �������� ������ ����
		bShowMouseCursor = false;
	}
	else
	{
		// ������ ������ ��������, �������� �������� Hovered ��� ��������� �� ������
		SetInputMode(FInputModeUIOnly());

		// ���������� ������ ����
		bShowMouseCursor = true;
	}
}



