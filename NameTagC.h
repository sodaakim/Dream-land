// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NameTagC.generated.h"

UCLASS()
class MYPROJECT2_API UNameTagC : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Name")
    void SetNameText(const FString& Name);

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* NameText;
};
