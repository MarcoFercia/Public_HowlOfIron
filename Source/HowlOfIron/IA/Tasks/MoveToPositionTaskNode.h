// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToPositionTaskNode.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UMoveToPositionTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector targetPositionKey;

private:
	UBlackboardComponent* blackboard;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual FString GetStaticDescription() const override;
};
