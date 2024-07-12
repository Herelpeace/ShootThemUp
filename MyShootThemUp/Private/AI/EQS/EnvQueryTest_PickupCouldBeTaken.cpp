// My Shoot Them Up Game , All Rights Reserved
// В EnvQueryTest_PickupCouldBeTaken.cpp


#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"
#include "Pickups/STUBasePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"


UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;                                      // сложность теста, зависит от математических операций применяемых к объектам. Low - когда нет математики 
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();	// может быть вектором/ актором в зависимости от того с каими данными будет работать тест 
	SetWorkOnFloatValues(false);                                    // какие переменные установить min, max, range, match. false - соответствует match, чисто логический тест
}

// запускается при вызове EQS 
void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// код получения булевого значения из функции теста 
	// при изменении значения в редакторе будет зафиксирована переменная в которой это сделали
	// она будет записана в BoolValue, это не чистый bool 
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	// чтобы из значения BoolValue получить чистое значение bool
	bool WantsBeTakable= BoolValue.GetValue();    

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		// получение актора 
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		// спавним его до пикапа, и проверям пикап это или нет 
		const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);

		if (!PickupActor) continue;

		// вызываем функцию проверки можно ли поднять данный пикап 
		const auto CouldBeTaken = PickupActor->CouldBeTaken();

		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
		// TestPurpose       - вид теста, выставляется в редакторе 
		// FilterType        - был установлен функцией SetWorkOnFloatValues(), у нас имеет значение Match 
		// CouldBeTaken      - значение score, можем ли мы поднимать данный пикап 
		// WantsBeTakable    - ожидаемые значения, если true - то успешными будут те кто принял значение true, если false то те кто не прошел тест 

	}

}