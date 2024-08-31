// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerController.h

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

	// ������� � ������� ���������� ������� input ������
	virtual void SetupInputComponent() override;

private:
	// Callback ������� ��� SetupInputComponent()
	void OnPauseGame();

	// Callback ������� ��� ��������� ��������� ���� 
	void OnMatchStateChanged(ESTUMatchState State);


};
