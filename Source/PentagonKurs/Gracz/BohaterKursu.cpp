// Fill out your copyright notice in the Description page of Project Settings.

#include "BohaterKursu.h"


// Sets default values
ABohaterKursu::ABohaterKursu()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABohaterKursu::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABohaterKursu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABohaterKursu::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABohaterKursu::ruchWPrzod(float Wartosc)
{
	if(Controller != NULL && Wartosc != 0)
	{
		// Wyciągamy globalną rotacje celem wyciągniecia z niej roacji w osi poziomej
		const FRotator RotacjaKontrolera = Controller->GetControlRotation();
		// Wyciagamy tylko os pionową
		const FRotator RotacjaYaw(0.0f, RotacjaKontrolera.Yaw, 0.0f);

		// Zamieniamy na wektor
		const FVector KierunekWSwiecie = RotacjaYaw.Vector();
		// Wreszcie wywołujemy funkcję
		this->AddMovementInput(KierunekWSwiecie,Wartosc);
	}
	
}

void ABohaterKursu::ruchWlewoPrawo(float Wartosc)
{
	if (Controller != NULL && Wartosc != 0)
	{
		// Wyciągamy globalną rotacje celem wyciągniecia z niej roacji w osi poziomej
		const FRotator RotacjaKontrolera = Controller->GetControlRotation();
		// Wyciagamy tylko os pionową
		const FRotator RotacjaYaw(0.0f, RotacjaKontrolera.Yaw, 0.0f);
		const FVector KierunekWSwiecie = FRotationMatrix(RotacjaYaw).GetUnitAxis(EAxis::Y);
		// Wreszcie wywołujemy funkcję
		this->AddMovementInput(KierunekWSwiecie, Wartosc);
	}
}

