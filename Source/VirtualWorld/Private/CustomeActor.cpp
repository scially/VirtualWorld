// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomeActor.h"
#include "MeshDescription.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"
#include "AssetRegistryModule.h"

// Sets default values
ACustomeActor::ACustomeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomeActorStaticMesh"));
	DisplayMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACustomeActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACustomeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomeActor::build(TArray<int32> &Indices, const TArray<FVector> &Verties)
{
	FName MeshName = MakeUniqueObjectName(nullptr, UStaticMesh::StaticClass(), BaseName);
	UPackage* SaveMeshPackage = CreatePackage(*(BasePath + MeshName.ToString()));
	
	UStaticMesh* StaticMesh = NewObject<UStaticMesh>(SaveMeshPackage, MeshName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	FAssetRegistryModule::AssetCreated(StaticMesh);

	FMeshDescription MeshDesc;
	FStaticMeshAttributes Attributes(MeshDesc);
	Attributes.Register();
	
	FMeshDescriptionBuilder MeshDescBuilder;
	MeshDescBuilder.SetMeshDescription(&MeshDesc);
	MeshDescBuilder.EnablePolyGroups();
	MeshDescBuilder.SetNumUVLayers(1);
	FPolygonGroupID PolygonGroup = MeshDescBuilder.AppendPolygonGroup();

	check(Indices.Num() % 3 == 0);

	for(int i = 0; i < Indices.Num() ; i+=3)
	{
		FVertexInstanceID Instance1 = MeshDescBuilder.AppendInstance(MeshDescBuilder.AppendVertex(Verties[Indices[i]]));
		MeshDescBuilder.SetInstanceNormal(Instance1, FVector(-0.7071, 0, 0.7071));			//法线
		MeshDescBuilder.SetInstanceUV(Instance1, FVector2D(0, 1), 0);				//UV
		MeshDescBuilder.SetInstanceColor(Instance1, FVector4(1.0f, 1.0f, 1.0f, 1.0f));	//顶点色
		
		
		FVertexInstanceID Instance2 = MeshDescBuilder.AppendInstance(MeshDescBuilder.AppendVertex(Verties[Indices[i+1]]));
		MeshDescBuilder.SetInstanceNormal(Instance1, FVector(-0.7071, 0, 0.7071));			//法线
		MeshDescBuilder.SetInstanceUV(Instance1, FVector2D(1, 0), 0);				//UV
		MeshDescBuilder.SetInstanceColor(Instance1, FVector4(1.0f, 1.0f, 1.0f, 1.0f));	//顶点色
		
		
		FVertexInstanceID Instance3 = MeshDescBuilder.AppendInstance(MeshDescBuilder.AppendVertex(Verties[Indices[i+2]]));
		MeshDescBuilder.SetInstanceNormal(Instance1, FVector(-0.7071, 0, 0.7071));			//法线
		MeshDescBuilder.SetInstanceUV(Instance1, FVector2D(0, 0), 0);				//UV
		MeshDescBuilder.SetInstanceColor(Instance1, FVector4(1.0f, 1.0f, 1.0f, 1.0f));	//顶点色

		MeshDescBuilder.AppendTriangle(Instance1, Instance2, Instance3, PolygonGroup);
	}
	UStaticMesh::FBuildMeshDescriptionsParams mdParams;
	mdParams.bBuildSimpleCollision = true;

	TArray<const FMeshDescription*> meshDescPtrs;
	meshDescPtrs.Emplace(&MeshDesc);
	
	StaticMesh->GetStaticMaterials().Add(FStaticMaterial());//至少添加一个材质
	StaticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);
	DisplayMesh->SetStaticMesh(StaticMesh);
	
}
