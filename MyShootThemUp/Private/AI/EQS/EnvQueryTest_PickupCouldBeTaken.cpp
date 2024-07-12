// My Shoot Them Up Game , All Rights Reserved
// � EnvQueryTest_PickupCouldBeTaken.cpp


#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"
#include "Pickups/STUBasePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"


UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;                                      // ��������� �����, ������� �� �������������� �������� ����������� � ��������. Low - ����� ��� ���������� 
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();	// ����� ���� ��������/ ������� � ����������� �� ���� � ����� ������� ����� �������� ���� 
	SetWorkOnFloatValues(false);                                    // ����� ���������� ���������� min, max, range, match. false - ������������� match, ����� ���������� ����
}

// ����������� ��� ������ EQS 
void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// ��� ��������� �������� �������� �� ������� ����� 
	// ��� ��������� �������� � ��������� ����� ������������� ���������� � ������� ��� �������
	// ��� ����� �������� � BoolValue, ��� �� ������ bool 
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	// ����� �� �������� BoolValue �������� ������ �������� bool
	bool WantsBeTakable= BoolValue.GetValue();    

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		// ��������� ������ 
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		// ������� ��� �� ������, � �������� ����� ��� ��� ��� 
		const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);

		if (!PickupActor) continue;

		// �������� ������� �������� ����� �� ������� ������ ����� 
		const auto CouldBeTaken = PickupActor->CouldBeTaken();

		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
		// TestPurpose       - ��� �����, ������������ � ��������� 
		// FilterType        - ��� ���������� �������� SetWorkOnFloatValues(), � ��� ����� �������� Match 
		// CouldBeTaken      - �������� score, ����� �� �� ��������� ������ ����� 
		// WantsBeTakable    - ��������� ��������, ���� true - �� ��������� ����� �� ��� ������ �������� true, ���� false �� �� ��� �� ������ ���� 

	}

}