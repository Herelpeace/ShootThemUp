// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerController.cpp


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


ASTUPlayerController::ASTUPlayerController()
{
	// создаем наш компонент RespawnComponent
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespwnComponent");
}


void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// подписываемся на делегат OnMatchStateChanged
	if (GetWorld())
	{
		// получаем текущий GameMode
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			// подписываемся на делегат состояния игры OnMatchStateChanged
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
			// будет вызываться функция OnMatchStateChanged
		}
	}

}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);

}

// функция в которой происходит биндинг input клавиш
void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// проверяем указатель InputComponent
	if (!InputComponent) return;

	// биндим кнопку паузы на функцию OnPauseGame
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
}


// Callback функция для SetupInputComponent()
void ASTUPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	// Вызываем функцию паузы которую переопределили в GameMode
	GetWorld()->GetAuthGameMode()->SetPause(this);

}


// Callback функция, которую подписываем на делегат изменения состояния игры в BeginPlay, OnMatchStateChanged
// вызывается каждый раз когда меняется состояние игры 
void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		// убирает курсор мыши
		// как бы делает дополнительный клик для скрытия курсора
		SetInputMode(FInputModeGameOnly());

		// скрываем курсор мыши
		bShowMouseCursor = false;
	}
	else
	{
		// делает курсор активным, начинает работать Hovered при наведении на кнопку
		SetInputMode(FInputModeUIOnly());

		// показываем курсор мыши
		bShowMouseCursor = true;
	}
}



