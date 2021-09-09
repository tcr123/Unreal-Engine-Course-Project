// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBT_ClearBlackboardValue::UBT_ClearBlackboardValue::UBT_ClearBlackboardValue() 
{
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBT_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    
    return EBTNodeResult::Succeeded;
}
