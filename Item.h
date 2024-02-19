// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "NameTagC.h"
#include "ItemData.h"
#include "Item.generated.h"

UCLASS()
class MYPROJECT2_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TriggerVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString ItemName = "ItemName";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    FItemData ItemData;

	void SetItemData(const FItemData& NewItemData);

};
