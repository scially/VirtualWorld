// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CustomeActor.generated.h"

class UProceduralMeshComponent;

UCLASS()
class VIRTUALWORLD_API ACustomeActor : public AActor
{
	GENERATED_BODY()
	
public:
	const inline static FString BasePath = TEXT("/Game/VirtualMeshes/");
	const inline static FName BaseName = TEXT("VirtualMesh");
	
	// Sets default values for this actor's properties
	ACustomeActor();
	
	UFUNCTION(BlueprintCallable)
	void build(TArray<int32> &Indices, const TArray<FVector> &Verties);

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> Owned_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DisplayMesh; 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
