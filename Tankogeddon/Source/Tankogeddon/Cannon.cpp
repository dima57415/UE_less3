// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(SceneComp);

	ProjectileSpawnComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnComponent->SetupAttachment(CannonMesh);

}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	bReadyToFire = true;
	bDelayToFire = true;
	Ammo = 10;
}

void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannon::Fire()
{
	if (!bReadyToFire || !bDelayToFire || Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Can't shooting");
		return;
	}
	if (CannonType == ECannonType::FireProjectile)
	{
		Ammo -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Fire Projectile, Ammo %d"), Ammo));
	}
	else
	{
		Ammo -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Fire trace, Ammo %d"), Ammo));
	}

	if (Ammo == 0)
	{
		bReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
	}
	
	bDelayToFire = false;
	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &ACannon::DelayFire_, FireDelay, false);
}

void ACannon::FireSpecial()
{
	if (!bReadyToFire || !bDelayToFire || Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Can't shooting");
		return;
	}
	if (CannonSpecialType == ECannonSpecialType::SpecialFire)
	{
		Ammo -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Fire Special, Ammo %d"), Ammo));
	}

	if (Ammo == 0)
	{
		bReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
	}
	bDelayToFire = false;
	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &ACannon::DelayFire_, FireDelay, false);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::Reload()
{
	bReadyToFire = true;
	Ammo = 10;
}

void ACannon::DelayFire_()
{
	bDelayToFire = true;
}
