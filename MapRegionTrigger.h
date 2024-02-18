#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "RegionWidget.h"
#include "MapRegionTrigger.generated.h"

UCLASS()
class MYPROJECT2_API AMapRegionTrigger : public AActor
{
    GENERATED_BODY()

public:    
    AMapRegionTrigger();

	void HideWidget();
	
protected:
    virtual void BeginPlay() override;

	FTimerHandle HideWidgetTimerHandle;

    UPROPERTY(VisibleAnywhere, Category = "Trigger")
    UBoxComponent* TriggerVolume;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<URegionWidget> RegionMessageWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	class URegionWidget* RegionWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
    FString RegionName;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
