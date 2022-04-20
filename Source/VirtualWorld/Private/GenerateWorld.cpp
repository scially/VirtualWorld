// Fill out your copyright notice in the Description page of Project Settings.

#include "GenerateWorld.h"
#include "GDALWrapper.h"
#include "CustomeActor.h"
#include "Utils.hpp"

// Sets default values
AGenerateWorld::AGenerateWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenerateWorld::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenerateWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AGenerateWorld::Transform(const FVector &Location) const
{
	// transform
	FVector TransformLocation = Location;;
	TransformLocation.X =  (DX + K * (Location.X * cos(T) + (-sin(T) * Location.Y))) * 100;
	TransformLocation.Y =  -(DY + K * (Location.X * sin(T) + ( cos(T) * Location.Y))) * 100;
	return TransformLocation;
}


AActor* AGenerateWorld::AssignOwnedProperties(UClass* AssigendActorClass, const TMap<FString, FString> &Properties) const
{
	AActor* SActor = GetWorld()->SpawnActor(AssigendActorClass);
	FProperty* OwnedProperty = AssigendActorClass->FindPropertyByName("Owned_");
		
	if(FMapProperty* MapOwnedProperty = CastField<FMapProperty>(OwnedProperty))
	{
		FScriptMap* MapScript = MapOwnedProperty->ContainerPtrToValuePtr<FScriptMap>(SActor);
		FScriptMapHelper MapHelper(MapOwnedProperty, MapScript);
			
		for (const auto& KV : Properties)
		{
			MapHelper.AddPair(&KV.Key, &KV.Value);	
		}
	}
	return SActor;
}

void AGenerateWorld::PointTypeGenerate(UClass* ActorSpawned) const
{
	GDALDatasetWrapper ds = GDALDatasetWrapper::open(DataPath);
	OGRLayerWrapper layer = ds.GetLayerByName(LayerName);
	OGRFeatureWrapper feature = layer.GetNextFeature();
	FString UUID = FGuid::NewGuid().ToString(EGuidFormats::Short);
	while (feature.isValid())
	{
		TMap<FString,FString> Owned;
		for(int i = 0; i < feature.GetFieldCount(); i++)
		{
			FString Name = UTF8_TO_TCHAR(feature.GetFieldDefnRef(i)->GetNameRef());
			FString Value= UTF8_TO_TCHAR(feature.GetFieldAsString(i));
			Owned.Add(Name, Value);
		}
		
		OGRGeometry* geom = feature.GetGeometryRef();
		float x = 0, y = 0;
		if(geom->getGeometryType() == wkbPoint || geom->getGeometryType() == wkbPoint25D)
		{
			OGRPoint* point = dynamic_cast<OGRPoint*>(geom);
			x = point->getX();
			y = point->getY();
		}
		else
		{
			OGREnvelope envelope;
			geom->getEnvelope(&envelope);
			x = (envelope.MinX + envelope.MaxX ) / 2;
			y = (envelope.MinY + envelope.MaxY ) / 2;
		}
		
		// spawn actor
		FVector Location = Transform(FVector(x, y, Z));
		AActor* SActor = AssignOwnedProperties(ActorSpawned, Owned);
		SActor->SetActorLocation(Location);
		FString SActorFolderPath = FString::Printf(TEXT("VirutalWorld-%s"), *UUID);
#if WITH_EDITOR 
		SActor->SetFolderPath(FName(*SActorFolderPath));
#endif
		
		feature = layer.GetNextFeature();
	}
}

void AGenerateWorld::GeomTypeGenerate() const
{
	GDALDatasetWrapper ds = GDALDatasetWrapper::open(DataPath);
	OGRLayerWrapper layer = ds.GetLayerByName(LayerName);
	OGRFeatureWrapper feature = layer.GetNextFeature();
	FString UUID = FGuid::NewGuid().ToString(EGuidFormats::Short);
	while (feature.isValid())
	{
		TMap<FString,FString> Owned;
		for(int i = 0; i < feature.GetFieldCount(); i++)
		{
			FString Name = UTF8_TO_TCHAR(feature.GetFieldDefnRef(i)->GetNameRef());
			FString Value= UTF8_TO_TCHAR(feature.GetFieldAsString(i));
			Owned.Add(Name, Value);
		}
		
		OGRGeometry* geom = feature.GetGeometryRef();
		float x = 0, y = 0;
		if(geom->getGeometryType() == wkbPolygon25D || geom->getGeometryType() == wkbPolygon)
		{
			OGRPolygon* polygon = dynamic_cast<OGRPolygon*>(geom);
			EarPolygon EPolygon = { {} };
			for(auto iter = polygon->begin(); iter != polygon->end(); iter++)
			{
				OGRLinearRing *ring = *iter;
				for(int ip = 0; ip < ring->getNumPoints(); ip++)
				{
					OGRPoint point;
					ring->getPoint(ip, &point);
					FVector TransformPt = Transform(FVector(point.getX(), point.getY(), 0));
					EPolygon[0].push_back(TransformPt);
				}
			}
			std::vector<int32> indices = mapbox::earcut<int32>(EPolygon);
			auto Indices = StdContainer2TArray(indices.rbegin(), indices.rend());
			ACustomeActor* CustomeActor = GetWorld()->SpawnActor<ACustomeActor>();
			CustomeActor->build(Indices, TArray<FVector>(&EPolygon[0][0],EPolygon[0].size()));
			// spawn actor
			CustomeActor->Owned_ = std::move(Owned);
#if WITH_EDITOR
			FString SActorFolderPath = FString::Printf(TEXT("VirutalWorld-%s"), *UUID);
			CustomeActor->SetFolderPath(FName(*SActorFolderPath));
#endif
		}
		feature = layer.GetNextFeature();
	}
}