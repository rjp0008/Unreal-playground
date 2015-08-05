// Fill out your copyright notice in the Description page of Project Settings.

#include "HowTo_PlayerInput.h"
#include "MyPawn.h"


// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this pawn to be controlled by the lowest numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create a dummy root component to attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	//attach our camera and visible object to the root
	OurCamera->AttachTo(RootComponent);
	(*OurVisibleComponent).AttachTo(RootComponent);

	//offset camera
	OurCamera->SetRelativeLocation(FVector(-250, 0, 250));

	//rotate camera
	OurCamera->SetRelativeRotation(FRotator(-45, 0, 0));
	InitLocation = GetActorLocation();
}

void AMyPawn::MoveXAxis(float AxisValue){

	//move at 100 units per second left or right
	CurrentAcceleration.X = CurrentAcceleration.X + FMath::Clamp(AxisValue, -1.0f, 1.0f) * 3;
}

void AMyPawn::MoveYAxis(float AxisValue){
	//move at 100 units per second left or right
	CurrentAcceleration.Y = CurrentAcceleration.Y + FMath::Clamp(AxisValue, -1.0f, 1.0f)*3;
}

void AMyPawn::StartGrowing(){
	isGrowing = true;
}

void AMyPawn::StopGrowing(){
	isGrowing = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (isGrowing){
			//double size in a second
			CurrentScale += DeltaTime;
		}
		else
		{
			//shrink half as fast as we grow
			CurrentScale -= (DeltaTime * 0.5f);
		}

		//Make sure we never drop below starting size, or increase past quad size
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 4.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	//placing cylinder logic
	{
			FVector NewLocation = GetActorLocation() + (CurrentAcceleration*.5 * DeltaTime);
			SetActorLocation(NewLocation);
			if (FMath::Abs(NewLocation.X) >= 500){
				CurrentAcceleration.X = .8*-CurrentAcceleration.X;
			}	
			if (FMath::Abs(NewLocation.Y) >= 500){
				CurrentAcceleration.Y = .8*-CurrentAcceleration.Y;
			}
	}


}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);


	//Respond to grow
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	//respond to move commands on ticks(frames)?
	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::MoveYAxis);


}

