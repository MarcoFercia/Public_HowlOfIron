// @AUTHOR: Germán López

#include "HICustomTrigger.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"

#pragma region UE_FUNCTIONS
AHICustomTrigger::AHICustomTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	debugCollider = CreateDefaultSubobject<UStaticMeshComponent>("DebugCollider");
	debugCollider->SetupAttachment(RootComponent);

	SetTriggerVisuals();
}

void AHICustomTrigger::AddTriggerEvent(UHITriggerEvent* addedTriggerEvent)
{
	triggerEvents.Add(addedTriggerEvent);
}

void AHICustomTrigger::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UHITriggerEvent> triggerEventClass : triggerEventClasses)
	{
		triggerEvents.Add(triggerEventClass.GetDefaultObject());
	}
	
	

	#if WITH_EDITOR
		if(enableDebug && GEngine)
		{
			SetActorHiddenInGame(false);
			GetRootComponent()->SetHiddenInGame(true);
			GetCollisionComponent()->SetHiddenInGame(true);
		}
	#endif
		
}

void AHICustomTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetTriggerVisuals();
}


void AHICustomTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(detectedActor.Num() == 0)
	{
		return;
	}
		
	for (int i = 0; i < detectedActor.Num(); i++)
	{
		if (OtherActor->GetClass() == detectedActor[i] && !triggered)
		{
			triggered = true;

			#if WITH_EDITOR
			if (enableDebug)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Triggered");
				if (triggeredMaterial != nullptr)
				{
					debugCollider->SetMaterial(0, triggeredMaterial);
				}
			}
			#endif

			if (triggerEvents.Num() != 0 && useTriggerEvent)
			{
				for (UHITriggerEvent* triggerEvent : triggerEvents)
				{
					if (enableDebug)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, triggerEvent->GetClass()->GetName());
					}

					triggerEvent->ExecuteTriggerEvent();
					triggerEvent->CodeExecuteTriggerEvent();
				}
				
			}

			//if (listeners.Num() != 0 && useTriggerEvent)
			//{
			//	for (AActor* listener : listeners)
			//	{
			//		//if (enableDebug)
			//		//{
			//		//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, triggerEvent->GetClass()->GetName());
			//		//}

			//		//triggerEvent->ExecuteTriggerEvent();
			//		//triggerEvent->CodeExecuteTriggerEvent();


			//	}

			//}
		}
	}
}
#pragma endregion

#pragma region SETTERS
void AHICustomTrigger::SetTriggerVisuals()
{
	#if WITH_EDITOR
		if (GEngine)
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> DebugMeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
			if (DebugMeshRef.Object != nullptr)
			{
				debugCollider->SetStaticMesh(DebugMeshRef.Object);
			}

			static ConstructorHelpers::FObjectFinder<UMaterial> DebugMeshMaterialRef(TEXT("Material'/Game/Logic/LevelDesign_Utilities/Materials/Debug/M_DebugMaterial_Blue.M_DebugMaterial_Blue'"));
			if (DebugMeshMaterialRef.Object != nullptr)
			{
				UMaterial* M = Cast<UMaterial>(DebugMeshMaterialRef.Object);
				debugCollider->SetMaterial(0, M);
				debugCollider->SetVisibility(true);
			}

			static ConstructorHelpers::FObjectFinder<UMaterial> DebugTriggeredMeshMaterialRef(TEXT("Material'/Game/Logic/LevelDesign_Utilities/Materials/Debug/M_DebugMaterial_Red.M_DebugMaterial_Red'"));
			if (DebugMeshMaterialRef.Object != nullptr)
			{
				triggeredMaterial = Cast<UMaterial>(DebugTriggeredMeshMaterialRef.Object);
				debugCollider->SetVisibility(true);
			}

		}
	#endif

	/*debugCollider->SetRelativeLocation(FVector());*/
	debugCollider->SetRelativeRotation(FRotator());
	debugCollider->SetRelativeScale3D(FVector(1.f));
	
	/*debugCollider->SetWorldLocation(GetActorLocation());*/
	debugCollider->SetWorldRotation(GetActorRotation());
	debugCollider->SetWorldScale3D((GetCollisionComponent()->GetCollisionShape().GetExtent()/40.f)/1.25f);
	
	debugCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	debugCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}
#pragma endregion
