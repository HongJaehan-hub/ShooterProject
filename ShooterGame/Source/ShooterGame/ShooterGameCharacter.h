// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterEventManager.h"
#include "ShooterGameCharacter.generated.h"


UCLASS(config=Game)
class AShooterGameCharacter : public ACharacter, public IEventListener
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	float RotationSpeed = 100.f;
public:
	AShooterGameCharacter();
	

public:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void ChangeMeshSkin(int32 SelectSkinIndex);
	inline int32 GetCurrentSkinIndex() {return SkinIndex;};

	// override IEventListener
	virtual void OnReceived(EEventType EventType, UEventParamBase* EventParam);
protected:
	
	// To add mapping context
	virtual void BeginPlay();
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
	TArray<USkeletalMesh*> SkinMeshes;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	int32 SkinIndex;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
	class AGun* PlayerGun;

private:
	UFUNCTION()
	void HideDefaultWeaponBone();

	UFUNCTION()
	void SpawnPlayerGun();

	void AddToEventListener();
};

