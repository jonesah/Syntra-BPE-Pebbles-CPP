// Fill out your copyright notice in the Description page of Project Settings.


#include "ADoor.h"

// Sets default values
AADoor::AADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(RootComponent);
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->AttachToComponent(Arrow, FAttachmentTransformRules::KeepRelativeTransform);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrameMesh");
	DoorFrame->AttachToComponent(Arrow, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(_isChangingState)
	{
		auto newAngle = FMath::FInterpTo(_currentAngle, _targetAngle, DeltaTime, 5); 
		
		// auto newAngle = FMath::Lerp(_currentAngle, _targetAngle, DeltaTime);
		DoorMesh->SetRelativeRotation(FRotator(0, newAngle, 0));
		_currentAngle = newAngle;
		if(FMath::IsNearlyEqual(_currentAngle, _targetAngle, 0.1))
		{
			_isChangingState = false;
			_isOpenedState = !_isOpenedState;
		}
	}
}

void AADoor::Open()
{
	_targetAngle = 90.0;
	_isChangingState = true;
}

void AADoor::Close()
{
	_targetAngle = 0.0;
	_isChangingState = true;
}

void AADoor::Toggle()
{
	if(_isOpenedState)
	{
		Close();
	} else
	{
		Open();
	}
}



