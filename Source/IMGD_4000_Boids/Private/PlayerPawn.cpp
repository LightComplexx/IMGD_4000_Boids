// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "ProjectileActor.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetRelativeLocation(FVector(-500.f, 0.f, 100.f));
	Camera->SetupAttachment(Mesh);

	ProjectileSpeed = 10.f;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn::Fire);
}


void APlayerPawn::MoveForward(float Amount) {
	PawnMovement->AddInputVector(GetActorUpVector() * Amount);
}

void APlayerPawn::MoveRight(float Amount) {
	PawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

void APlayerPawn::Fire() {
	FVector start = GetActorLocation();
	start.Z += 50.f;
	start.Y -= 80.f;

	float distance = 2000.f;
	FVector fv = GetActorForwardVector();
	FVector end = ((fv * distance) + start);

	DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, 2.f, 0, 5.f);

	FCollisionQueryParams cqp;
	FHitResult hr;
	GetWorld()->LineTraceSingleByChannel(hr, start, end, ECC_Visibility, cqp);
	if (hr.bBlockingHit == true) {
		if (hr.GetActor() != this) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("HIT! %s"), *hr.GetActor()->GetName()));
			UE_LOG(LogTemp, Warning, TEXT("HIT! %s"), *hr.GetActor()->GetName());

			HitSomething_Implementation(Cast<UStaticMeshComponent>(hr.GetActor()->GetRootComponent()));
		}
	}
}

void APlayerPawn::HitSomething_Implementation(class UStaticMeshComponent* meshThatWasHit) {
	HitSomething(meshThatWasHit);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("HIT SOMETHING CALLED")));
	//UE_LOG(LogTemp, Warning, TEXT(“HIT SOMETHING CALLED”));
}