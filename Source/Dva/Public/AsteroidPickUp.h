// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.h"
#include "AsteroidPickUp.generated.h"

UCLASS()
class DVA_API AAsteroidPickUp : public APickUpBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
