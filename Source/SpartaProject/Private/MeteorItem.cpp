#include "MeteorItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AMeteorItem::AMeteorItem()
{
    ExplosionDelay = 0.1f;
    ExplosionRadius = 300.0f;
    ExplosionDamage = 30.0f;
    ItemType = "Meteor";
    bHasExploded = false;

    ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
    ExplosionCollision->InitSphereRadius(ExplosionRadius);
    ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    ExplosionCollision->SetupAttachment(Scene);
}

void AMeteorItem::ActivateItem(AActor* Activator)
{

}

void AMeteorItem::Explode()
{
    UParticleSystemComponent* Particle = nullptr;
    if (ExplosionParticle)
    {
        Particle = UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionParticle,
            GetActorLocation(),
            GetActorRotation(),
            false
        );
    }

    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            GetWorld(),
            ExplosionSound,
            GetActorLocation()
        );
    }

    TArray<AActor*> OverlappingActors;
    ExplosionCollision->GetOverlappingActors(OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        if (Actor && Actor->ActorHasTag("Player"))
        {
            // 데미지를 발생시켜 Actor->TakeDamage()가 실행되도록 함
            UGameplayStatics::ApplyDamage(
                Actor,                      // 데미지를 받을 액터
                ExplosionDamage,            // 데미지 양
                nullptr,                    // 데미지를 유발한 주체 (지뢰를 설치한 캐릭터가 없으므로 nullptr)
                this,                       // 데미지를 유발한 오브젝트(지뢰)
                UDamageType::StaticClass()  // 기본 데미지 유형
            );
        }
    }

    // 지뢰 제거
    DestroyItem();

    if (Particle)
    {
        FTimerHandle DestroyParticleTimerHandle;

        GetWorld()->GetTimerManager().SetTimer(
            DestroyParticleTimerHandle,
            [Particle]()
            {
                if (IsValid(Particle)) // 유효성 체크
                {
                    Particle->DestroyComponent();
                }
            },
            2.0f,
            false
        );
    }
}

void AMeteorItem::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(
        ExplosionTimerHandle,
        [this]()
        {
            if (IsValid(this))  // 유효한 객체인지 확인
            {
                Explode();
            }
        },
        ExplosionDelay,
        false
    );
    bHasExploded = true;
}