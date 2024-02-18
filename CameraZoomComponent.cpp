#include "CameraZoomComponent.h"


UCameraZoomComponent::UCameraZoomComponent()
{
    PrimaryComponentTick.bCanEverTick = true; // Enable ticking for this component
    CurrentZoom = 600.0f; // Initialize zoom level
}

void UCameraZoomComponent::BeginPlay()
{
    Super::BeginPlay();

    CameraSpringArm = GetOwner()->FindComponentByClass<USpringArmComponent>();
    if (CameraSpringArm)
    {
        CurrentZoom = CameraSpringArm->TargetArmLength;
        UE_LOG(LogTemp, Warning, TEXT("CameraSpringArm is found and CurrentZoom is %f"), CurrentZoom);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CameraSpringArm is NOT found."));
    }
}

void UCameraZoomComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UCameraZoomComponent::ZoomIn()
{
    if (CameraSpringArm)
    {
        UE_LOG(LogTemp, Warning, TEXT("Zooming Inn")); 
        CurrentZoom = FMath::Clamp(CurrentZoom - ZoomSpeed, MinZoom, MaxZoom);
        CameraSpringArm->TargetArmLength = CurrentZoom; // 실제로 줌인을 조절
    }
}

void UCameraZoomComponent::ZoomOut()
{
    if (CameraSpringArm)
    {
        UE_LOG(LogTemp, Warning, TEXT("Zooming Outt")); 
        CurrentZoom = FMath::Clamp(CurrentZoom + ZoomSpeed, MinZoom, MaxZoom);
        CameraSpringArm->TargetArmLength = CurrentZoom; // 실제로 줌아웃을 조절
    }
}