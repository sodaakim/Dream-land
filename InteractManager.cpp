#include "InteractManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UInteractManager::UInteractManager()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInteractManager::BeginPlay()
{
    Super::BeginPlay();
    SetupInputComponent();
}

void UInteractManager::SetupInputComponent()
{
     APlayerController* PC = Cast<APlayerController>(GetOwner());
    if (PC && PC->InputComponent)
    {
        PC->InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractManager::Interact);
    }
}


void UInteractManager::Interact()
{
    // 가장 가까운 NPC 찾기
    NearestNPC = FindNearestNPC();
    UE_LOG(LogTemp, Warning, TEXT("NearNPC NAME = %s"), *NearestNPC->GetName());
    UE_LOG(LogTemp, Warning, TEXT("bCanInteract = %s"), NearestNPC->bCanInteract ? TEXT("True") : TEXT("False"));

    if(NearestNPC && NearestNPC->bCanInteract) // 상호작용 가능한 경우에만
    {
        ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
        APlayerController* PlayerController = Cast<APlayerController>(CharacterOwner->GetController());
        if (CharacterOwner && PlayerController)
        {
            NearestNPC->OpenNPCWidget(PlayerController);
        }
    }
}


ANPC* UInteractManager::FindNearestNPC()
{
    // 가장 가까운 NPC를 찾기 위한 로직 구현
    // 예: GetAllActorsOfClass 사용 및 가장 가까운 액터 찾기
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPC::StaticClass(), FoundActors);

    NearestNPC = nullptr;
    float NearestDistanceSq = FLT_MAX;

    for (AActor* Actor : FoundActors)
    {
        NPC = Cast<ANPC>(Actor);
        if (NPC)
        {
            float DistanceSq = (NPC->GetActorLocation() - GetOwner()->GetActorLocation()).SizeSquared();
            if (DistanceSq < NearestDistanceSq)
            {
                NearestDistanceSq = DistanceSq;
                NearestNPC = NPC;
            }
        }
    }

    return NearestNPC;
}

void UInteractManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Here you can implement any ticking logic you need
}
