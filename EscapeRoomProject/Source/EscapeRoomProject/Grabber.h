// MarcSau

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:

public:
	// Methods
	virtual void BeginPlay() override;
	void SetAtachedInputComponent();
	void FindPhysicsHandlerComponenet();
	void Grab();
	void Release();
	const FHitResult GetFirstPhysicBodyInReach();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//Variables
	AActor * Owner;
	APlayerController* OwnerController;
	class UPhysicsHandleComponent* PhysicsHandleVariable = nullptr;
	class UInputComponent* InputComponentVariable = nullptr;
	UPROPERTY(EditAnywhere)
	float Reach = 150.0;

	//Raycast and grab whats in front
	
};
