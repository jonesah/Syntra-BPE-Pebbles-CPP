// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Light.h"
#include "GameFramework/Actor.h"
#include "ATriggerArea.generated.h"

UCLASS()
class PEBBLES_API AATriggerArea : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AATriggerArea();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Cylinder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UCapsuleComponent> CollisionCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetLights")
	TArray<ALight*> TargetLights;

	UFUNCTION(BlueprintCallable, Category = "ATriggerArea")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
