// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lapacz.generated.h"

class UPhysicsHandleComponent;
class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENTAGONKURS_API ULapacz : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULapacz();
private:
	FVector wyliczKoniec(float zasieg);
	bool wykonajTrace(FHitResult &Hit);
	/*
	Wyznacza zasięg traceowania
	*/
	UPROPERTY(EditDefaultsOnly,Category = "Podnoszenie")
	float zasiegTrace =  500.0f;
	float zasiegNoszenia = 300.0f;
	UPhysicsHandleComponent* FizycznyPodnosnik = nullptr;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/*Zmienia zasięg noszenia,
	public zeby byla dostępna z 
	*/
	UFUNCTION(BlueprintCallable, Category = "Podnoszenie")
	void zmienZasieg(float input);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void podnies();
	void upusc();
	void setPhysicsHandleComponent();
	
};
