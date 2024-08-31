// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCoreType.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;


UCLASS()
class MYSHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASTUPlayerController();


	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	USTURespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	// функция в которой происходит биндинг input клавиш
	virtual void SetupInputComponent() override;

private:
	// Callback функция для SetupInputComponent()
	void OnPauseGame();

	// Callback функция при изменения состояния игры 
	void OnMatchStateChanged(ESTUMatchState State);


};
