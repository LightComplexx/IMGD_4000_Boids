// Copyright Epic Games, Inc. All Rights Reserved.


#include "IMGD_4000_BoidsGameModeBase.h"

AIMGD_4000_BoidsGameModeBase::AIMGD_4000_BoidsGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}

void AIMGD_4000_BoidsGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));
    Manager = NewObject<UFlockingManager>();
    Manager->Init(GetWorld(), AgentMesh);
}

void AIMGD_4000_BoidsGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    Manager->Flock();
};