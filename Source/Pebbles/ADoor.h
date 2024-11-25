#pragma once

#include "Components/ArrowComponent.h"
#include "ADoor.generated.h"

UCLASS(config=Game)
class ADoor : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(Category=Geometry, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Arrow;
	
	UPROPERTY(Category=Geometry, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(Category=Geometry, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh;

	bool IsOpen = false;
	bool InMotion = false;
	float To = 90;

	
	ADoor();

	void Open();
	void Close();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
};

