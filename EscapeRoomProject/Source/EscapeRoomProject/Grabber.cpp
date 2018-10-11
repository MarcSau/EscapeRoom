// MarcSau

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Public/Math/Vector.h"
#include "Public/Math/Rotator.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	OwnerController = GetWorld()->GetFirstPlayerController();

	// ...
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewpointLocation;
	FRotator PlayerViewRotator;

	OwnerController->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewRotator);

	FVector EndLine = PlayerViewpointLocation + PlayerViewRotator.Vector() * Reach;

	DrawDebugLine(
		GetWorld(), 
		PlayerViewpointLocation, 
		EndLine,
		FColor(255,0,0),
		false,
		0.f,
		0,
		10
	);

	//Setup
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());
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
		UE_LOG(LogTemp, Warning, TEXT("Name: %s "),  *ActorHit->GetName());
	}
	//

	// ...
}

