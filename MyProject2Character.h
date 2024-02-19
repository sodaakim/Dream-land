// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "InputActionValue.h"
#include "CameraZoomComponent.h"
#include "InteractManager.h"
#include "ItemData.h"
#include "Inventory.h"
#include "MyProject2Character.generated.h"


UCLASS(config=Game)
class AMyProject2Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AMyProject2Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraZoomComponent* CameraZoomComponent;		

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractManager")
    UInteractManager* InteractComponent;		

	UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UInventory> InventoryWidgetClass;

	UPROPERTY()
    UInventory* InventoryWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
    TArray<FItemData> InventoryItems;

	int32 InventoryRows = 5;
	int32 InventoryColumns = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Coins = 200;

	void OpenInventory(); //Press I
	void UpdateCoinDisplay();
	void CloseInventory();

	void RemoveItemFromInventory(const FGuid& ItemID);
	void AddItemToInventory(const FItemData& ItemToAdd);

protected:

	void OnZoomIn();
    void OnZoomOut();

	void OnInteract(); //Press E

	void PickupItem(); //Press P


	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

