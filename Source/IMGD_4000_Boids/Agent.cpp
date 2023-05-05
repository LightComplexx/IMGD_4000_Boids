// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

// Sets default values
AAgent::AAgent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
	RootComponent = Mesh;

	//SetActorRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	MaxSpeed = 10.f;
	MinSpeed = 4.f;
	MaxForce = 0.2f;

	float direction = FMath::FRandRange(-1.f, 1.f);

	Velocity = FVector(FMath::FRandRange(4.f, 10.f) * direction);
	Acceleration = FVector(0.f);
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();

}

void AAgent::Init(UStaticMeshComponent* mesh, int id) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgent::Update(TArray<class AAgent*> Agents) {
	FVector loc = GetActorLocation();
	FVector alignment = Align(Agents);
	FVector cohesion = Cohesion(Agents);
	FVector separation = Separation(Agents);

	SetActorLocation(loc + Velocity);

	Acceleration += alignment;
	Acceleration += cohesion;
	Acceleration += separation;
	Velocity += Acceleration;
	Velocity = Velocity.GetClampedToSize(MinSpeed, MaxSpeed);

	edges();

	// reset acceleration so it doesn't accumulate
	Acceleration = FVector(0.f);

}

FVector AAgent::Align(TArray<class AAgent*> Agents) {
	FVector steering = FVector(0.f);
	float perceptionRadius = 100.f;
	float total = 0.f;

	for (AAgent* OtherAgent : Agents) {
		float distance = FVector::Distance(GetActorLocation(), OtherAgent->GetActorLocation());

		if (OtherAgent != this && distance < perceptionRadius) {
			steering += OtherAgent->Velocity;
			total++;
		}
	}

	if (total > 0) {
		steering /= total;
		steering -= Velocity;
		steering = steering.GetClampedToMaxSize(MaxForce);
	}

	return steering;
}

FVector AAgent::Cohesion(TArray<class AAgent*> Agents) {
	FVector steering = FVector(0.f);
	float perceptionRadius = 200.f;
	float total = 0.f;

	for (AAgent* OtherAgent : Agents) {
		float distance = FVector::Distance(GetActorLocation(), OtherAgent->GetActorLocation());

		if (OtherAgent != this && distance < perceptionRadius) {
			steering += OtherAgent->GetActorLocation();
			total++;
		}
	}

	if (total > 0) {
		steering /= total;
		steering -= GetActorLocation();
		steering -= Velocity;
		steering = steering.GetClampedToMaxSize(MaxForce);
	}

	return steering;
}

FVector AAgent::Separation(TArray<class AAgent*> Agents) {
	FVector steering = FVector(0.f);
	float perceptionRadius = 100.f;
	float total = 0.f;

	for (AAgent* OtherAgent : Agents) {
		float distance = FVector::Distance(GetActorLocation(), OtherAgent->GetActorLocation());

		if (OtherAgent != this && distance < perceptionRadius) {
			FVector diff = GetActorLocation() - OtherAgent->GetActorLocation();
			diff /= distance;
			steering += diff;
			total++;
		}
	}

	if (total > 0) {
		steering /= total;
		steering -= Velocity;
		steering = steering.GetClampedToMaxSize(MaxForce);
	}

	return steering;
}

void AAgent::edges() {
	if (GetActorLocation().X < -1000) {
		SetActorLocation(FVector(1000.0, GetActorLocation().Y, GetActorLocation().Z));
	}
	else if (GetActorLocation().X > 1030) {
		SetActorLocation(FVector(-1000.0, GetActorLocation().Y, GetActorLocation().Z));
	}

	if (GetActorLocation().Y < -1000) {
		SetActorLocation(FVector(GetActorLocation().X, 1000, GetActorLocation().Z));
	}
	else if (GetActorLocation().Y > 1000) {
		SetActorLocation(FVector(GetActorLocation().X, -1000, GetActorLocation().Z));
	}

	if (GetActorLocation().Z < -50) {
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 1000));
	}
	else if (GetActorLocation().Z > 1000) {
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0));
	}
}

