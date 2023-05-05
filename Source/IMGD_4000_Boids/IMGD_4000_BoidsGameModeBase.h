// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "IMGD_4000_BoidsGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class IMGD_4000_BOIDS_API AIMGD_4000_BoidsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AIMGD_4000_BoidsGameModeBase();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* AgentMesh;

	UPROPERTY() UFlockingManager* Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
