// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetTeamID(int32 ID) { TeamID = ID; }
	int32 GetTeamID() const { return TeamID; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() const { return TeamColor; }

	void AddKill() { ++KillsNum; }
	int32 GetKillsNum() const { return KillsNum; }

	void AddDeath() { ++DeathNum; }
	int32 GetDeathNum() const { return DeathNum; }

	// выводит данные статистики в консоль
	void LogInfo();


private:
	int32 TeamID;			 // номер команды
	FLinearColor TeamColor;	 // цвет команды

	int32 KillsNum = 0;		// количество убитых врагов
	int32 DeathNum = 0;		// количество смертей
	
};
