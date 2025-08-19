// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponClassBufferImplementor.h"
#include "JanitorCharacter.h"

// Sets default values
AWeaponClassBufferImplementor::AWeaponClassBufferImplementor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWeaponClassBufferImplementor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponClassBufferImplementor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponClassBufferImplementor::Attack()
{
}

void AWeaponClassBufferImplementor::AerialAttack()
{
}

void AWeaponClassBufferImplementor::ModeAttack()
{
}

void AWeaponClassBufferImplementor::ModeAerialAttack()
{
}

void AWeaponClassBufferImplementor::ForwardAttack()
{
}

void AWeaponClassBufferImplementor::BackwardAttack()
{
}

void AWeaponClassBufferImplementor::LeftwardAttack()
{
}

void AWeaponClassBufferImplementor::RightwardAttack()
{
}

void AWeaponClassBufferImplementor::AerialForwardAttack()
{
}

void AWeaponClassBufferImplementor::AerialBackwardAttack()
{
}

void AWeaponClassBufferImplementor::AerialLeftwardAttack()
{
}

void AWeaponClassBufferImplementor::AerialRightwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeForwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeBackwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeLeftwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeRightwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeAerialForwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeAerialBackwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeAerialLeftwardAttack()
{
}

void AWeaponClassBufferImplementor::ModeAerialRightwardAttack()
{
}

UStaticMeshComponent* AWeaponClassBufferImplementor::GetMesh()
{
	return nullptr;
}

void AWeaponClassBufferImplementor::DoAttack(DirectionENUM Direction)
{
	if (!janitor->GetIsLockedOn())
	{
		if (!janitor->GetIsAirborne())
			Attack();
		else AerialAttack();
	}
	else
	{
		if (Direction == DirectionENUM::Front)
		{
			if (!janitor->GetIsAirborne())
				ForwardAttack();
			else AerialForwardAttack();
		}
		else if (Direction == DirectionENUM::Back)
		{
			if (!janitor->GetIsAirborne())
				BackwardAttack();
			else AerialBackwardAttack();
		}
		else if (Direction == DirectionENUM::Left)
		{
			if (!janitor->GetIsAirborne())
				LeftwardAttack();
			else AerialLeftwardAttack();
		}
		else if (Direction == DirectionENUM::Right)
		{
			if (!janitor->GetIsAirborne())
				RightwardAttack();
			else AerialRightwardAttack();
		}
		else
		{
			if (!janitor->GetIsAirborne())
				Attack();
			else AerialAttack();
		}
	}
}

void AWeaponClassBufferImplementor::DoModeAttack(DirectionENUM Direction)
{
	if (!janitor->GetIsLockedOn())
	{
		if (!janitor->GetIsAirborne())
			ModeAttack();
		else ModeAerialAttack();
	}
	else
	{
		if (Direction == DirectionENUM::Front)
		{
			if (!janitor->GetIsAirborne())
				ModeForwardAttack();
			else ModeAerialForwardAttack();
		}
		else if (Direction == DirectionENUM::Back)
		{
			if (!janitor->GetIsAirborne())
				ModeBackwardAttack();
			else ModeAerialBackwardAttack();
		}
		else if (Direction == DirectionENUM::Left)
		{
			if (!janitor->GetIsAirborne())
				ModeLeftwardAttack();
			else ModeAerialLeftwardAttack();
		}
		else if (Direction == DirectionENUM::Right)
		{
			if (!janitor->GetIsAirborne())
				ModeRightwardAttack();
			else ModeAerialRightwardAttack();
		}
		else
		{
			if (!janitor->GetIsAirborne())
				ModeAttack();
			else ModeAerialAttack();
		}
	}
}

TArray<UHurtBox*> AWeaponClassBufferImplementor::GetHurtBoxArray()
{
	return m_HurtBoxArr;
}

UAnimMontage* AWeaponClassBufferImplementor::getRecoveryMontage()
{
	return m_RecoveryMontage;
}

void AWeaponClassBufferImplementor::setRecoveryMontage(UAnimMontage* recoveryMontage)
{
	m_RecoveryMontage = recoveryMontage;
}
