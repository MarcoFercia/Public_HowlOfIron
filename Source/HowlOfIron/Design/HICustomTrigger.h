// @AUTHOR: Germán López

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HITriggerEvent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Engine/TriggerBox.h"
#include "HICustomTrigger.generated.h"


/**
 * 
 */
UCLASS()
class HOWLOFIRON_API AHICustomTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	AHICustomTrigger();

public:
	void AddTriggerEvent(UHITriggerEvent* addedTriggerEvent);

protected:
	#pragma region UE_FUNCTIONS
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	#pragma endregion 
private:
	#pragma region SETTERS
	/// <summary>
	/// Set trigger box and material for editor purposes.
	/// </summary>
	void SetTriggerVisuals();
	#pragma endregion 


public:
	#pragma region CUSTOM_TRIGGER_VARIABLES

	/// <summary>
	/// Shows trigger in game mode.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Data")
	bool enableDebug;

	/// <summary>
	/// Allow to use a custom actor to be detected.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Data|Class References", meta=(InlineEditConditionToggle))
	bool useDetectedActor;
	
	/// <summary>
	/// Actor classes which are detected by the trigger.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Data|Class References", meta=(ToolTip="Sets which actor is detected by the trigger.", EditCondition="useDetectedActor"))
	TArray<TSubclassOf<AActor>> detectedActor;

	/// <summary>
	/// Actor classes which are detected by the trigger.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Data|Class References", meta = (ToolTip = "Sets listener.", EditCondition = "useDetectedActor"))
		TArray<TSubclassOf<AActor>> listeners;
	
	/// <summary>
	/// Allows to use a trigger event.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Data|Class References", meta=(InlineEditConditionToggle))
	bool useTriggerEvent;
	
	/// <summary>
	/// Event classes of the events which are called after activating the trigger.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Data|Class References", meta=(DisplayName="Trigger Event", ToolTip="Sets which custom task is executed after being triggered.", EditCondition="useTriggerEvent"))
	TArray<TSubclassOf<UHITriggerEvent>> triggerEventClasses;
	#pragma endregion 


protected:
	#pragma region UE_FUNCTIONS
	UFUNCTION(BlueprintCallable)
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	#pragma endregion 


private:
	#pragma region CUSTOM_TRIGGER_READONLY_VARIABLES
	/// <summary>
	/// Determines if the trigger was already used.
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Trigger Data|Read Only", meta=(EditCondition="enableDebug", EditConditionHides))
	bool triggered;

	/// <summary>
	/// Mesh component which implements the triggeredMaterial (for editor purposes).
	/// </summary>
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger Data|Read Only", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* debugCollider;

	/// <summary>
	/// Material used when is triggered (for editor purposes).
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Trigger Data|Read Only", meta=(EditCondition="enableDebug", EditConditionHides))
	UMaterial* triggeredMaterial;

	/// <summary>
	/// Events which are called after activating the trigger.
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Trigger Data|Read Only")
	TArray<UHITriggerEvent*> triggerEvents;
	#pragma endregion 
};


