#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraZoomComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UCameraZoomComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UCameraZoomComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    void ZoomIn();
    void ZoomOut();

private:
    UPROPERTY(EditAnywhere, Category="Camera")
    float ZoomSpeed = 100.0f; // Speed at which the camera zooms in/out

    UPROPERTY(EditAnywhere, Category="Camera")
    float MaxZoom = 1200.0f; // Max distance for camera zoom out

    UPROPERTY(EditAnywhere, Category="Camera")
    float MinZoom = 300.0f; // Min distance for camera zoom in

    float CurrentZoom; // Current zoom level
    USpringArmComponent* CameraSpringArm; // Spring arm component for the camera
};
