// My Shoot Them Up Game , All Rights Reserved
// В STUEnemyEnvQueryContext.h

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STUEnemyEnvQueryContext.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";		// имя ключа вражеского актора, который используем в Blackboard
};
