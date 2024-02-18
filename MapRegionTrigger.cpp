#include "MapRegionTrigger.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"

AMapRegionTrigger::AMapRegionTrigger()
{
    PrimaryActorTick.bCanEverTick = true;

    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    RootComponent = TriggerVolume;
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMapRegionTrigger::OnOverlapBegin);
    TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMapRegionTrigger::OnOverlapEnd);
}

void AMapRegionTrigger::BeginPlay()
{
    Super::BeginPlay();
    
    if (GetNetMode() != NM_DedicatedServer) // 서버가 아닌 경우에만 실행
    {
        UE_LOG(LogTemp, Warning, TEXT("Region Widget Created"));
        if(IsValid(RegionMessageWidgetClass)) {
            RegionWidget = Cast<URegionWidget>(CreateWidget(GetWorld(), RegionMessageWidgetClass));
            FString Message = FString::Printf(TEXT("%s에 진입했습니다."), *RegionName);
            RegionWidget->SetRegionName(Message);
            RegionWidget->AddToViewport();
            RegionWidget->SetVisibility(ESlateVisibility::Hidden);        
        }
    }
}


void AMapRegionTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 로컬 플레이어 캐릭터를 가져옵니다.
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());

    // OtherActor를 ACharacter로 캐스팅합니다.
    ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);

    // 캐스팅된 OtherCharacter와 로컬 플레이어 캐릭터를 비교합니다.
    if (OtherCharacter && OtherCharacter == PlayerCharacter && IsValid(RegionWidget))
    {
        UE_LOG(LogTemp, Warning, TEXT("Enter %s"), *RegionName);
        RegionWidget->SetVisibility(ESlateVisibility::Visible);
        GetWorld()->GetTimerManager().SetTimer(HideWidgetTimerHandle, this, &AMapRegionTrigger::HideWidget, 5.0f, false);
    }
}


void AMapRegionTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd called with OtherActor: %s"), *GetNameSafe(OtherActor));
    if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && IsValid(RegionWidget))
    {
        UE_LOG(LogTemp, Warning, TEXT("Exit %s"), *RegionName);
        RegionWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}


void AMapRegionTrigger::HideWidget()
{
    if (RegionWidget) {
        RegionWidget->SetVisibility(ESlateVisibility::Hidden);
    }
	// 타이머 취소
    GetWorld()->GetTimerManager().ClearTimer(HideWidgetTimerHandle);
}
