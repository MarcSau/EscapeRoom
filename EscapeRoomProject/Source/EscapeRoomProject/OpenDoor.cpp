// MarcSau

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	ActorDoorOpener=GetWorld()->GetFirstPlayerController()->GetPawn();
	
	// ...
	
}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();

	FRotator Rotation = FRotator(0,OpenAngle,0);
	
	Owner->SetActorRotation(Rotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate) {
		if(ActorDoorOpener && PressurePlate->IsOverlappingActor(ActorDoorOpener)){
			OpenDoor();
		}
	}
	
	
	
	// ...
}

