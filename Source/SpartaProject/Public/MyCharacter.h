// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

UCLASS()
class SPARTAPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	
public:
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;
	
	// ���� ü���� �������� �Լ�
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;
	// ü���� ȸ����Ű�� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);
	// �ӵ��� ���ҽ�Ű�� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Slowing")
	void AddSlowing(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Slowing")
	void ReturnSlowing();
	
	UFUNCTION(BlueprintCallable, Category = "ReverseControl")
	void ReverseControl();
	UFUNCTION(BlueprintCallable, Category = "ReverseControl")
	void ReturnControl();
	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	// ���� ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;



protected:


	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ������ ó�� �Լ� - �ܺηκ��� �������� ���� �� ȣ���
	// �Ǵ� AActor�� TakeDamage()�� �������̵�
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;


	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);



	// ��� ó�� �Լ� (ü���� 0 ���ϰ� �Ǿ��� �� ȣ��)
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();
	void UpdateOverheadHP();

	FTimerHandle SlowTimerHandle;
	FTimerHandle ControlTimerHandle;

private:
	float Speed;
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
	float SlowingSpeed;
	float SlowingSpeedMultiplier;

	int32 control;
};
