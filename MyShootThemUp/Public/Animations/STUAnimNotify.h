// My Shoot Them Up Game , All Rights Reserved
// В STUAnimNotify.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUAnimNotify.generated.h"

// объявляем делегат, по указателю USkeletalMeshComponent* определяем, если анимация не для нашего скелета, то Notify для неё не обрабатываем
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);


UCLASS()
class MYSHOOTTHEMUP_API USTUAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// функция через которую мы можем получить доступ к событию Notify ?
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// создаем объект делегата
	FOnNotifiedSignature OnNotified;
	
};
