// Fill out your copyright notice in the Description page of Project Settings.

#include "Lapacz.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"



// Sets default values for this component's properties
ULapacz::ULapacz()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


FVector ULapacz::wyliczKoniec(float zasieg)
{
	// poczatek tracowania
	FVector poczatek = this->GetOwner()->GetActorLocation();
	// potrzebny tylko do wywolania funkcji, nie potrzebny inaczej
	FVector temp;
	//rotor przechowujacy rotacje
	FRotator rotacja;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(temp,rotacja);
	FVector rotVector = rotacja.Vector();
	
	// zwróc policzoną rotacje
	return poczatek + rotVector * zasieg;
}

bool ULapacz::wykonajTrace(FHitResult & Hit)
{
	// przechowuje lokacje startową trace'owania, czyli pozycje naszego gracza
	FVector poczatekTrace = this->GetOwner()->GetActorLocation();
	// przechowuje wyliczony koniec trace'owania
	FVector koniecTrace = wyliczKoniec(zasiegTrace);
	// przechowuje typy obiektów przeciw którym sprawdzamy traceing
	FCollisionObjectQueryParams coSzukamy = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	/* Dodatkowe parametry traceowania
	Tag trace -> pusty bo ""
	false -> zapytanie czy sprawdzac kompleksową kolizje
	GetOwner() -> wyciągamy aktora przeciw któremu traceing bedzie ignorowany, omijamy w ten sposób stan w którym traceujemy samego siebie
	*/
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	//Debug line do traceowania
	UE_LOG(LogTemp, Warning, TEXT("WOHO"));

	DrawDebugLine(this->GetWorld(), poczatekTrace, koniecTrace, FColor::Purple, false, -1.0);
	// Funkcja wykonująca traceing
	return this->GetWorld()->LineTraceSingleByObjectType(Hit,
		poczatekTrace,
		koniecTrace,
		coSzukamy,
		TraceParams

	);
}
/* Wywolujemy to z blueprintów


*/
void ULapacz::zmienZasieg(float input)
{
	UE_LOG(LogTemp, Warning, TEXT("Wartosc floata %f"),zasiegNoszenia);
	zasiegNoszenia += input * 5;
}

// Called when the game starts
void ULapacz::BeginPlay()
{
	Super::BeginPlay();
	setPhysicsHandleComponent();
	// ...
	
}


// Called every frame
void ULapacz::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// sprawdzam czy podnosnik istnieje, zabezpieczajac wskaznik
	if (!FizycznyPodnosnik) return;
	// sprawdzam czy podnoszony przedmiot istnieje
	if (FizycznyPodnosnik->GrabbedComponent)
	{
		// wyliczam koniec lini
		FizycznyPodnosnik->SetTargetLocation(wyliczKoniec(zasiegNoszenia));
	}
	// ...
}

void ULapacz::podnies()
{
	// Przechowuje wynik traceowania , np co trafilismy
	FHitResult wynikTraceowania;
	// Wykonujemy Traceowanie
	if (wykonajTrace(wynikTraceowania))
	{
	 // wyciagam ztraceowany przedmiot z wyniku traceowania
	auto podnoszonyPrzedmiot = wynikTraceowania.GetComponent();
	// sprawdzam na wszelki wypadek czy zarówno podnosnik nie jest nullem chroniąc wskaźnik
	if (!FizycznyPodnosnik ) return;
	// podnosze przedmiot
	FizycznyPodnosnik->GrabComponent(podnoszonyPrzedmiot, NAME_None, podnoszonyPrzedmiot->GetOwner()->GetActorLocation(), true);
	}
}

void ULapacz::upusc()
{
	// zabezpieczenie wskaznika
	if (!FizycznyPodnosnik) return;
	// upuszczam przedmiot
	FizycznyPodnosnik->ReleaseComponent();
}

void ULapacz::setPhysicsHandleComponent()
{
	// znajdz component typu UPhysicsHandleComponent
	FizycznyPodnosnik = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// wyswietl loga jesli znalazles handlecomponent
	if (FizycznyPodnosnik) UE_LOG(LogTemp, Warning, TEXT("Znaleziono podnosnik"));
}

