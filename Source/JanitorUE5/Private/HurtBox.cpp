// Fill out your copyright notice in the Description page of Project Settings.


#include "HurtBox.h"


UHurtBox::UHurtBox()
{
	bIsActive = false;
	bCanBeActivated = false;
	m_AttackName = "";
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionResponseToAllChannels(ECR_Overlap);

}

UHurtBox::~UHurtBox()
{
}

bool UHurtBox::GetIsActive() const
{
	return bIsActive;
}

void UHurtBox::SetIsActive(bool newIsActive)
{
	bIsActive = newIsActive;
}

bool UHurtBox::GetCanBeActivated() const
{//this line seems to be creating problems and making the game crash but i can't seem to recreate it, i thought it was because the array of hurtboxes was not getting filled in the hurtboxanimnotifystate class, or maybe something wasn't getting initialized properly.
	return bCanBeActivated;
}

void UHurtBox::SetCanBeActivated(bool newCanBeActivated)
{
	bCanBeActivated = newCanBeActivated;
}

StatusEffect UHurtBox::GetStatusEffect()
{
	return m_StatusEffect;
}

void UHurtBox::SetStatusEffect(StatusEffect newStatusEffect)
{
	m_StatusEffect = newStatusEffect;
}

FName UHurtBox::GetAttackName() const
{
	return m_AttackName;
}

void UHurtBox::SetAttackName(FName NewAttackName)
{
	m_AttackName = NewAttackName;
}

void UHurtBox::ClearAttackName()
{
	m_AttackName = "";
}

