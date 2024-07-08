// My Shoot Them Up Game , All Rights Reserved
// � STUEnemyEnvQueryContext.cpp


#include "AI/EQS/STUEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	// �������� ������ 
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	// �������� Blackboard
	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	// QueryOwner - ��������� �� ����� 
	// ������� ������ ���� ������ �� pawn, �� ���� �������� Controller,� �� ���� Blackboard

	if (!Blackboard) return;

	const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
	// ������� ��������� ������, ������� ������ ����

}