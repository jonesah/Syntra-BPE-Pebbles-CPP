// Fill out your copyright notice in the Description page of Project Settings.


#include "ATriggerArea.h"

#include "Engine/Light.h"


// Sets default values
AATriggerArea::AATriggerArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>("Cylinder");
	Cylinder->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("CollisionCapsule");
	CollisionCapsule->AttachToComponent(Cylinder, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AATriggerArea::BeginPlay()
{
	Super::BeginPlay();
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AATriggerArea::OnOverlapBegin);
}

// Called every frame
void AATriggerArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATriggerArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow,
	"TriggerArea TRIGGERED");
	}

	for (auto Light : TargetLights)
	{
		Light->SetEnabled(false);
	}

}
