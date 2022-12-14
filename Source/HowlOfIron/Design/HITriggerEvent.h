// @AUTHOR: Germán López

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HITriggerEvent.generated.h"

UCLASS(Blueprintable, BlueprintType, config = Engine)
class HOWLOFIRON_API UHITriggerEvent : public UObject
{
	GENERATED_BODY()
	
public:	
	UHITriggerEvent();

public:
	#pragma region CUSTOM_TASK_FUNCTIONS
	/// <summary>
	/// Executes the trigger event.
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	void ExecuteTriggerEvent();

	/// <summary>
	/// Executes the trigger event. This method is expected to be override by code
	/// </summary>
	virtual void CodeExecuteTriggerEvent();
	#pragma endregion 
};
