// My Shoot Them Up Game , All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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



};
