#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "DialogueWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "PressE.h"
#include "NameTagC.h"
#include "NPCWidget.h"
#include "Shop.h"
#include "ItemData.h"
#include "NPC.generated.h"

UCLASS()
class MYPROJECT2_API ANPC : public ACharacter
{
    GENERATED_BODY()

public:    
    ANPC();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;


public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TriggerVolume;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UPressE> PressEClass;
    UPressE* PressE = nullptr;

    bool bCanInteract = false; 

    bool bShouldLookAtPlayer = false;
    bool bTurnBack = false;
    FRotator OriginalRotation;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UDialogueWidget> DialogueWidgetClass;
    UDialogueWidget* DialogueWidget = nullptr;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UNPCWidget> NPCWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Greeting = "HIHIHIHI";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString JobName;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UShop> ShopClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString ShopName = "'s Shop";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shop")
    TArray<FItemData> ItemsForSale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TArray<FString> Dialogue;
    int32 CurrentDialogueIndex = 0;


    UFUNCTION()
    void OpenNPCWidget(APlayerController* PlayerController);
    
    UFUNCTION()
    void OpenShopWidget(APlayerController* PlayerController);
    
    UFUNCTION()
    void StartDialogue(APlayerController* PlayerController);

    UFUNCTION()
    void HandleDialogueClosed();
    void UpdateDialogueWidget(APlayerController* PlayerController);
    void CloseWidget();

    void LookAtPlayerLocally(ACharacter* PlayerCharacter, float DeltaTime);
    void TurnBackLocally(float DeltaTime);

    //UFUNCTION(Client, Reliable)
    //void CreatePressEWidgetOnClient();

};
