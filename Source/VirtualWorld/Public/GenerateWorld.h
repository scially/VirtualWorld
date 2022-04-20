// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EarCut.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenerateWorld.generated.h"

using EPoint = FVector;
using EarPolygon = std::vector<std::vector<EPoint>>;

UCLASS()
class VIRTUALWORLD_API AGenerateWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateWorld();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	float DX = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	float DY = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	float T = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	float K = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	FString DataPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	FString LayerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GenerateWorld")
	float Z = 0.0f;
	
	UFUNCTION(BlueprintCallable, Category="GenerateWorld")
	void PointTypeGenerate(UClass* ActorSpawned) const;
	UFUNCTION(BlueprintCallable, Category="GenerateWorld")
	void GeomTypeGenerate() const;
	
	FVector Transform(const FVector &Location) const;
	AActor* AssignOwnedProperties(UClass* AssigendActorClass, const TMap<FString, FString> &Properties) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


namespace mapbox {
	namespace util {
		template <>
		struct nth<1, EPoint> {
			inline static float get(const EPoint &t) {
				return t.Y;
			};
		};
		
		template <>
		struct nth<0, EPoint> {
			inline static float get(const EPoint &t) {
				return t.X;
			};
		};
	} // namespace util
} // namespace mapbox