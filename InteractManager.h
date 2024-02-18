#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "NPC.h"
#include "InteractManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UInteractManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    // Sets default values for this component's properties
    UInteractManager();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetupInputComponent();
    void Interact();

    ANPC* FindNearestNPC();
    ANPC* NearestNPC;
    ANPC* NPC;

private:
    UInputComponent* InputComponent;
};
