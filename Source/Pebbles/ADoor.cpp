#include "ADoor.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	
    DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	DoorFrameMesh->AttachToComponent(Arrow, FAttachmentTransformRules::KeepRelativeTransform);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->AttachToComponent(Arrow, FAttachmentTransformRules::KeepRelativeTransform);

	IsOpen = false;
	
}

void ADoor::Open()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,
			"Opening Door");

	InMotion = true;
	To = 90;
}

void ADoor::Close()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,
			"Opening Door");

	InMotion = true;
	To = 0;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(InMotion)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,
				"Door moving");
		FQuat targetRotator = FQuat(FRotator(0,To,0));
		FQuat newAngle = FMath::Lerp(
			DoorMesh->GetComponentRotation().Quaternion(),
			targetRotator,
			0.01f);

		DoorMesh->SetWorldRotation(newAngle);

		
		auto yaw = newAngle.Rotator().Yaw;
		if(FMath::IsNearlyEqual(yaw, To, 0.1))
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,
					"Door motion complete");

			InMotion = false;
			IsOpen = !IsOpen;
		}
	}
}

