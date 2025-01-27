// Fill out your copyright notice in the Description page of Project Settings.

#include "HowTo_PlayerInput.h"
#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	initLoc = CameraOne->GetActorLocation();
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 5.0f;
	const float SmoothBlendTime = 0.75f;
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f){
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController){
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr)){
				CameraOne->SetActorLocation(initLoc);
				OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
			}
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr)){
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
		}
	}
	FVector location = CameraOne->GetActorLocation();
	location.X += 20.0f * DeltaTime;
	CameraOne->SetActorLocation(location);
}

