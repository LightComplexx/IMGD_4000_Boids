// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Agent.generated.h"

UCLASS()
class IMGD_4000_BOIDS_API AAgent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAgent();
	void Init(UStaticMeshComponent* mesh, int id);
	UStaticMeshComponent* Mesh;

	FVector Velocity;
	FVector Acceleration;
	float MaxForce;
	float MaxSpeed;
	float MinSpeed;

	void Update(TArray<class AAgent*> Agents);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector Align(TArray<class AAgent*> Agents);
	FVector Cohesion(TArray<class AAgent*> Agents);
	FVector Separation(TArray<class AAgent*> Agents);

	void edges();
};
