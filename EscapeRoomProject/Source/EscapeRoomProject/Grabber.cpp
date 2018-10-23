// MarcSau

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Public/Math/Vector.h"
#include "Public/Math/Rotator.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::Grab() {

	auto RaycastOut = GetFirstPhysicBodyInReach();
	auto ComponentToGrab = RaycastOut.GetComponent();
	auto Actorhit = RaycastOut.GetActor();

	//Line trace and see if any actor with psysics body channel set
	if (Actorhit) {
		PhysicsHandleVariable->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
	
	//Is hit atach physics handle to actor
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Error, TEXT("Released "));
	PhysicsHandleVariable->ReleaseComponent();
	//If object atached to physics handle release object

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	OwnerController = GetWorld()->GetFirstPlayerController();
	FindPhysicsHandlerComponenet();
	SetAtachedInputComponent();
	
}

void UGrabber::SetAtachedInputComponent()
{
	InputComponentVariable = Owner->FindComponentByClass<UInputComponent>();
	if (InputComponentVariable) {
		InputComponentVariable->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponentVariable->BindAction("Release", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandlerComponenet()
{
	PhysicsHandleVariable = Owner->FindComponentByClass<UPhysicsHandleComponent>();
}


const FHitResult UGrabber::GetFirstPhysicBodyInReach()
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewRotator;
	OwnerController->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewRotator);
	FVector EndLine = PlayerViewpointLocation + PlayerViewRotator.Vector() * Reach;
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());

	/*DrawDebugLine(
		GetWorld(), PlayerViewpointLocation, EndLine, FColor(255, 0, 0), false, 0, 0, 10
	);*/

	//LLancem raycast
	FHitResult RaycastOut;
	GetWorld()->LineTraceSingleByObjectType(
		OUT RaycastOut,
		PlayerViewpointLocation,
		EndLine,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParam);

	AActor * ActorHit = RaycastOut.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Grabed %s"), *ActorHit->GetName());
	}
	return RaycastOut;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Setup
	if (PhysicsHandleVariable->GrabbedComponent) {
		FVector PlayerViewpointLocation;
		FRotator PlayerViewRotator;
		OwnerController->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewRotator);
		FVector EndLine = PlayerViewpointLocation + PlayerViewRotator.Vector() * Reach;

		PhysicsHandleVariable->SetTargetLocation(EndLine);
	}
	//
	
	// ...
}

