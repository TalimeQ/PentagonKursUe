// Fill out your copyright notice in the Description page of Project Settings.

#include "BohaterKursu.h"
#include "Gracz/Komponenty/Lapacz.h"


// Sets default values
ABohaterKursu::ABohaterKursu()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sprawia że przy ruchu myszką nie będziemy kręcić się cali, a wyłącznie będziemy kręcić kamerą
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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
	// Raczej nie powinno dojść do stanu w którym ten wskaźnik będzie nullem, ale przezorny zawsze ubezpieczony
	if (!PlayerInputComponent) return; 
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis Inputs
	PlayerInputComponent->BindAxis("Turn", this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	// Action inputs
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Podnies", IE_Pressed, this, &ABohaterKursu::podnies);
	PlayerInputComponent->BindAction("Podnies", IE_Released, this, &ABohaterKursu::upusc);
		// Tutaj nie znajdziesz czelendza:) znacznie czysciej bylo mi to zaimplementować jako blueprint ;)

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

void ABohaterKursu::zmienZasieg(float Wartosc)
{
	UE_LOG(LogTemp, Warning, TEXT("Zmien zasieg 1"));
	if (!podnosnik) return;
	podnosnik->zmienZasieg(Wartosc);
}

void ABohaterKursu::podnies()
{
	if (!podnosnik) return;
	podnosnik->podnies();
}

void ABohaterKursu::upusc()
{
	this->podnosnik->upusc();
}

void ABohaterKursu::setPodnosnik(ULapacz * _podnosnik)
{
	this->podnosnik = _podnosnik;
}

