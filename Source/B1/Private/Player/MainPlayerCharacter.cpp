// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/HealthComponent.h"
#include "Components/PlayerCharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "Weapon/WeaponActorComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterCompLog, All, All);

AMainPlayerCharacter::AMainPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UPlayerCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArm);

	WeaponComponent = CreateDefaultSubobject<UWeaponActorComponent>("WeaponComponentMyawweq");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	
}

float AMainPlayerCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
		return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnDeath.AddUObject(this, &AMainPlayerCharacter::OnDeath);
	
	LandedDelegate.AddDynamic(this, &AMainPlayerCharacter::OnGroundLanded);
}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMainPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayerCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AMainPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponActorComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponActorComponent::StopFire);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, WeaponComponent, &UWeaponActorComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponActorComponent::Reload);

}

void AMainPlayerCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void AMainPlayerCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AMainPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AMainPlayerCharacter::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}

void AMainPlayerCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);

}

void AMainPlayerCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(2.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();
}


void AMainPlayerCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	UE_LOG(BaseCharacterCompLog, Display, TEXT("Fall %f"), FallVelocityZ);
	if (FallVelocityZ < LandedVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr); 
}
