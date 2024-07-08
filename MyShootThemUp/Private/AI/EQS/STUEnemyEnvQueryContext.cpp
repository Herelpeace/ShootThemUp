// My Shoot Them Up Game , All Rights Reserved
// В STUEnemyEnvQueryContext.cpp


#include "AI/EQS/STUEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	// получаем актора 
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	// получаем Blackboard
	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	// QueryOwner - указатель на актор 
	// функция делает каст актора до pawn, из него получает Controller,а из него Blackboard

	if (!Blackboard) return;

	const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
	// функция принимает актора, поэтому делаем каст

}