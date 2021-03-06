﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BohaterKursu.generated.h"

class ULapacz;

UCLASS()
class PENTAGONKURS_API ABohaterKursu : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABohaterKursu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION(BlueprintCallable,Category = "Movement")
	void ruchWPrzod(float Wartosc);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ruchWlewoPrawo(float Wartosc);
	
	void zmienZasieg(float Wartosc);

	UFUNCTION(BlueprintCallable, Category = "Podnoszenie")
		void podnies();
	UFUNCTION(BlueprintCallable, Category = "Podnoszenie")
		void upusc();
	UFUNCTION(BlueprintCallable, Category = "Podnoszenie")
		void setPodnosnik(ULapacz * _podnosnik);
	// Wskaznik do komponentu podnoszącego
	ULapacz* podnosnik = nullptr;
	
};
