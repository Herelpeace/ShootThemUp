// My Shoot Them Up Game , All Rights Reserved
// � STUAnimNotify.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUAnimNotify.generated.h"

// ��������� �������, �� ��������� USkeletalMeshComponent* ����������, ���� �������� �� ��� ������ �������, �� Notify ��� �� �� ������������
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);


UCLASS()
class MYSHOOTTHEMUP_API USTUAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// ������� ����� ������� �� ����� �������� ������ � ������� Notify ?
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// ������� ������ ��������
	FOnNotifiedSignature OnNotified;
	
};
