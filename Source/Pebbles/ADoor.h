// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "ADoor.generated.h"

UCLASS()
class PEBBLES_API AADoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Angle, meta = (AllowPrivateAccess))
	float _currentAngle = 0.0f;
	float _targetAngle = 90.0f;
	bool _isChangingState = false;
	bool _isOpenedState = false;
	
public:	
	// Sets default values for this actor's properties
	AADoor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorFrame;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Open();
	void Close();
	void Toggle();
};
