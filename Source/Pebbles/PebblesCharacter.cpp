// Copyright Epic Games, Inc. All Rights Reserved.

#include "PebblesCharacter.h"

#include "ADoor.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Elements/Framework/TypedElementUtil.h"
#include "Weapons/ProjectileWeapon.h"
#include "Weapons/Weapon.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APebblesCharacter

APebblesCharacter::APebblesCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

// 	Weapon* myFirstWeapon = new Weapon("Bonecleaver" , 5);
// 	Weapon* mySecondWeapon = new Weapon("FonsDeSpons", 1);
// 	if(GEngine)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// 	"This weapon named " + myFirstWeapon->GetName() + " does damage in the amount of " + FString::FromInt(myFirstWeapon->Damage));
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// 	"This weapon named " + mySecondWeapon->GetName() + " does damage in the amount of " + FString::FromInt(mySecondWeapon->Damage));
// 	}
// 	
// 	ProjectileWeapon* myProjectileWeapon = new ProjectileWeapon("DeGooier", 20, 6);
// 	ProjectileWeapon* myOtherProjectileWeapon = new ProjectileWeapon("EierDooier", 15, 12);
// 	
// 	if(GEngine)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// "This weapon named " + myProjectileWeapon->GetName() + " has ammo " +
// 			FString::FromInt(myProjectileWeapon->Ammo) + " does damage in the amount of " + FString::FromInt(myProjectileWeapon->Damage));
//
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// "This weapon named " + myOtherProjectileWeapon->GetName() + " has ammo " +
// 			FString::FromInt(myOtherProjectileWeapon->Ammo) + " does damage in the amount of " + FString::FromInt(myOtherProjectileWeapon->Damage));
// 	}
// 	
// 	//character earns fast reload perk
// 	myOtherProjectileWeapon->SetReloadSpeed(1);
	
}

void APebblesCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void APebblesCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	// FString hello = "C++ Hello";
	// _counter++;
	//
	// if(GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	// 		hello + FString::FromInt(_counter));

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	TArray<AActor*> actorsToIgnore; 
	actorsToIgnore.Add(GetOwner());

	TArray<AActor*> outActors;
	
	auto isColliding =  UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		200,
		objectTypes,
		nullptr,
		actorsToIgnore,
		outActors
	);

	if(!isColliding)
		return;

	_interactionTarget = outActors[0];

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,
			"Press E to interact with " + _interactionTarget -> GetName());
}

//////////////////////////////////////////////////////////////////////////
// Input

void APebblesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APebblesCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APebblesCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APebblesCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APebblesCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APebblesCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APebblesCharacter::Interact(const FInputActionValue& Value)
{
	if(_interactionTarget == nullptr)
		return;

	ADoor* door = Cast<ADoor>(_interactionTarget);
	if(door != nullptr)
	{
		if(door->IsOpen)
		{
			door->Open();	
		}
		else
		{
			door->Close();
		}
		
	}
}