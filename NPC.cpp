#include "NPC.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyProject2Character.h"
#include "NameTagC.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;

    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    RootComponent = TriggerVolume;
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    //bReplicates = true;
    //TriggerVolume->SetIsReplicated(true);
    
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
    TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
    OriginalRotation = GetActorRotation();
    UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();
    if (WidgetComp)
    {
        WidgetComp->SetVisibility(false);
        UUserWidget* Widget = Cast<UUserWidget>(WidgetComp->GetUserWidgetObject());
        if (Widget)
        {
            UNameTagC* NameTagWidget = Cast<UNameTagC>(Widget);
            if (NameTagWidget)
            {
                NameTagWidget->SetNameText(JobName);
                bCanInteract = true;
            }
        }
    }
}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 예시: 상호작용 상태일 때만 플레이어를 바라보게 함
    if (bShouldLookAtPlayer)
    {
        ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (PlayerCharacter)
        {
            LookAtPlayerLocally(PlayerCharacter, DeltaTime);
        }
    }
    if (bTurnBack)
    {
        TurnBackLocally(DeltaTime);
    }
}

void ANPC::LookAtPlayerLocally(ACharacter* PlayerCharacter, float DeltaTime)
{
    if (PlayerCharacter && GetNetMode() == NM_Client)
    {
        FVector Direction = PlayerCharacter->GetActorLocation() - GetActorLocation();
        Direction.Normalize();
        FRotator TargetRot = FRotationMatrix::MakeFromX(Direction).Rotator();
        TargetRot.Pitch = 0.0f; // Pitch와 Roll은 조정하지 않음
        TargetRot.Roll = 0.0f;
        FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, 5.0f); // 보간 속도는 조절 가능
        SetActorRotation(NewRot);
    }
}

void ANPC::TurnBackLocally(float DeltaTime)
{
    FRotator NewRot = FMath::RInterpTo(GetActorRotation(), OriginalRotation, DeltaTime, 5.0f); // 보간 속도는 조절 가능
    SetActorRotation(NewRot);

    if (FMath::IsNearlyEqual(GetActorRotation().Yaw, OriginalRotation.Yaw, 1.0f) &&
        FMath::IsNearlyEqual(GetActorRotation().Pitch, OriginalRotation.Pitch, 1.0f) &&
        FMath::IsNearlyEqual(GetActorRotation().Roll, OriginalRotation.Roll, 1.0f))
    {
        bTurnBack = false; // 회전 완료
    }
}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor)
    {
        // OtherActor의 클래스 이름을 로그로 출력
        UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin with actor: %s"), *OtherActor->GetName());
        
        // OtherActor의 클래스 타입을 로그로 출력
        UE_LOG(LogTemp, Warning, TEXT("Class of OtherActor: %s"), *OtherActor->GetClass()->GetName());
    }
    
    ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (OtherActor == PlayerCharacter)
    {
        UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();
        if (WidgetComp)
        {
            WidgetComp->SetVisibility(true); // 이름표를 보이게 함
        }
    }
   
    if (GetNetMode() == NM_Client)
    {
        // 로컬 플레이어 캐릭터와 로컬 플레이어 컨트롤러를 가져옵니다.
        UE_LOG(LogTemp, Warning, TEXT("overlap"));
        ACharacter* LocalPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
        APlayerController* LocalPlayerController = UGameplayStatics::GetPlayerController(this, 0);

        // 오버랩한 액터가 로컬 플레이어 캐릭터인지 확인하고, 이벤트가 클라이언트에서 실행되고 있는지 확인합니다.
        if (OtherActor == LocalPlayerCharacter && GetNetMode() != NM_DedicatedServer)
        {
            bCanInteract = true;
            UE_LOG(LogTemp, Warning, TEXT("bCanInteract = %s"), bCanInteract ? TEXT("True") : TEXT("False"));
            
            // 이미 PressE 위젯이 생성되지 않았는지 확인하고, 생성되지 않았다면 생성합니다.
            if (IsValid(PressEClass)) 
            { 
                UE_LOG(LogTemp, Warning, TEXT("Creating pressE widget"));
                PressE = CreateWidget<UPressE>(LocalPlayerController, PressEClass);
                PressE->AddToViewport();
                UE_LOG(LogTemp, Warning, TEXT("bCanInteract = %s"), bCanInteract ? TEXT("True") : TEXT("False"));
            }
        }
    }
}


void ANPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (OtherActor == PlayerCharacter)
    {
        UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();
        if (WidgetComp)
        {
            WidgetComp->SetVisibility(false); // 이름표를 숨김
        }
    }

    bCanInteract = false; // 플레이어가 상호작용할 수 없음
    if (PressE) { PressE->RemoveFromParent(); PressE = nullptr; }
}


void ANPC::OpenNPCWidget(APlayerController* PlayerController)
{

    UE_LOG(LogTemp, Warning, TEXT("Start NPCWidget"));
    if (!PlayerController || !bCanInteract || !NPCWidgetClass) return;
    UNPCWidget* NPCWidget = CreateWidget<UNPCWidget>(PlayerController, NPCWidgetClass);
    bShouldLookAtPlayer = true;
    if (NPCWidget)
    {
        NPCWidget->SetJobName(JobName);
        NPCWidget->SetDialogue(Greeting);
        NPCWidget->InitializeNPC(this);  // ANPC 참조를 UNPCWidget에 전달
        NPCWidget->AddToViewport();
    }
    if (PressE) { PressE->RemoveFromParent(); PressE = nullptr; }
    PlayerController->bShowMouseCursor = true;

    ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
    if (PlayerCharacter)
    {
        PlayerCharacter->DisableInput(PlayerController);
        PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
    }
}

void ANPC::OpenShopWidget(APlayerController* PlayerController)
{
    if (!PlayerController || !ShopClass) return;

    UE_LOG(LogTemp, Warning, TEXT("OpenShop called"));
    UShop* ShopWidget = CreateWidget<UShop>(PlayerController, ShopClass);
    ShopWidget->AddToViewport();
    ShopWidget->SetShopText(JobName+ShopName);
    ShopWidget->InitializeGrid(5, 5, this);
    PlayerController->bShowMouseCursor = true;

    AMyProject2Character* PlayerCharacter = Cast<AMyProject2Character>(PlayerController->GetPawn());
    if (PlayerCharacter)
    {
        PlayerCharacter->OpenInventory();
    }

}

void ANPC::StartDialogue(APlayerController* PlayerController)
{
    UE_LOG(LogTemp, Warning, TEXT("Start Dialogue"));
    if (!PlayerController || Dialogue.IsEmpty() || CurrentDialogueIndex >= Dialogue.Num()) return;
    if (!DialogueWidget) { DialogueWidget = CreateWidget<UDialogueWidget>(PlayerController, DialogueWidgetClass); }
    DialogueWidget->InitializeWithNPC(this);
    if (DialogueWidget) { UpdateDialogueWidget(PlayerController); }
}


void ANPC::HandleDialogueClosed()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    CurrentDialogueIndex++;
    if (CurrentDialogueIndex < Dialogue.Num()) { StartDialogue(PC); }
    else { CloseWidget(); }
}

void ANPC::UpdateDialogueWidget(APlayerController* PlayerController)
{
    FString CurrentDialogueText = Dialogue.IsValidIndex(CurrentDialogueIndex) ? Dialogue[CurrentDialogueIndex] : FString();
    DialogueWidget->SetDialogue(CurrentDialogueText);
    DialogueWidget->SetJobName(JobName);
    DialogueWidget->SetNextBtnText(CurrentDialogueIndex < Dialogue.Num() - 1 ? TEXT("넘어가기") : TEXT("대화종료"));

    DialogueWidget->AddToViewport();

    PlayerController->SetInputMode(FInputModeUIOnly());
    PlayerController->bShowMouseCursor = true;

    DialogueWidget->OnDialogueClosed.RemoveDynamic(this, &ANPC::HandleDialogueClosed);
    DialogueWidget->OnDialogueClosed.AddDynamic(this, &ANPC::HandleDialogueClosed);
}

void ANPC::CloseWidget()
{
    UE_LOG(LogTemp, Warning, TEXT("Close Dialogue"));
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if(PC)
    {
        PC->bShowMouseCursor = false;

        // AMyProject2Character 타입으로 다운캐스트
        AMyProject2Character* PlayerCharacter = Cast<AMyProject2Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if(PlayerCharacter)
        {
            PlayerCharacter->EnableInput(PC);

            // 인벤토리 위젯을 닫습니다.
            PlayerCharacter->CloseInventory();
        }
    }
    PC->SetInputMode(FInputModeGameOnly());
    PC->bShowMouseCursor = false;
    CurrentDialogueIndex = 0; // 대화 인덱스 초기화
    bShouldLookAtPlayer = false;
    bTurnBack = true;
}
