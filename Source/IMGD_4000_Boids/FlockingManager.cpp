// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 10

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
	UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

	World = world;
	float incr = (PI * 2.f) / AGENT_COUNT;
	for (int i = 0; i < AGENT_COUNT; i++) {
		if (World != nullptr) {
			FRotator rotation = FRotator();

			FVector location = FVector();
			location.X = FMath::Sin(incr * i) * 300.f;
			location.Z = FMath::Cos(incr * i) * 300.f;

			AAgent* agent = World->SpawnActor<AAgent>(location + FVector(0.f, 0.f, 350.f), rotation);
			agent->Init(mesh, i);
			Agents.Add(agent);
		}
	}

	initialized = true;
}

void UFlockingManager::Flock() {
	for (AAgent* Agent : Agents) {
		Agent->Update(Agents);
	}
}
