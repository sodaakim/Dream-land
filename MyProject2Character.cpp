#include "MyProject2Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AMyProject2Character

AMyProject2Character::AMyProject2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// CameraZoomComponent 생성 및 초기화
	CameraZoomComponent = CreateDefaultSubobject<UCameraZoomComponent>(TEXT("CameraZoomComponent"));
	UE_LOG(LogTemp, Warning, TEXT("CameraZoomComponent is %s"), CameraZoomComponent ? *CameraZoomComponent->GetName() : TEXT("null"));

	InteractComponent = CreateDefaultSubobject<UInteractManager>(TEXT("InteractManager"));
	UE_LOG(LogTemp, Warning, TEXT("InteractManager is %s"), InteractComponent ? *InteractComponent->GetName() : TEXT("null"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMyProject2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProject2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyProject2Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyProject2Character::Look);

	}
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 액션 매핑 바인딩
    PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMyProject2Character::OnZoomIn);
    PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMyProject2Character::OnZoomOut);

	//Press E
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyProject2Character::OnInteract);

	//Press I
	PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &AMyProject2Character::OpenInventory);
}

void AMyProject2Character::OnZoomIn()
{
    // 줌인 로직 구현
    if (CameraZoomComponent)
    {
        CameraZoomComponent->ZoomIn();
    }
}

void AMyProject2Character::OnZoomOut()
{
    // 줌아웃 로직 구현
    if (CameraZoomComponent)
    {
        CameraZoomComponent->ZoomOut();
    }
}

void AMyProject2Character::OnInteract()
{
	if (InteractComponent)
    {
        InteractComponent->Interact();
    }
}

void AMyProject2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyProject2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


void AMyProject2Character::OpenInventory()
{
	if (InventoryWidget && InventoryWidget->IsInViewport()) return;
    InventoryWidget = CreateWidget<UInventory>(GetWorld(), InventoryWidgetClass);
    if (InventoryWidget)
    {
        InventoryWidget->AddToViewport();
		InventoryWidget->SetCoinText(Coins);
        InventoryWidget->InitializeGrid(InventoryRows, InventoryColumns, this);
    }
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly()); // UI 전용 입력 모드로 설정
	}
}

void AMyProject2Character::UpdateCoinDisplay()
{
	if (InventoryWidget)
	{
		InventoryWidget->SetCoinText(Coins);
	}
}

void AMyProject2Character::CloseInventory()
{
    if (InventoryWidget != nullptr)
    {
        InventoryWidget->RemoveFromParent();
        InventoryWidget = nullptr; // 위젯 참조를 제거합니다.
    }
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly()); // 게임 전용 입력 모드로 설정
	}
}

