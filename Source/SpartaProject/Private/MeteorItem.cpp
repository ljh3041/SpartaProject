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
            // �������� �߻����� Actor->TakeDamage()�� ����ǵ��� ��
            UGameplayStatics::ApplyDamage(
                Actor,                      // �������� ���� ����
                ExplosionDamage,            // ������ ��
                nullptr,                    // �������� ������ ��ü (���ڸ� ��ġ�� ĳ���Ͱ� �����Ƿ� nullptr)
                this,                       // �������� ������ ������Ʈ(����)
                UDamageType::StaticClass()  // �⺻ ������ ����
            );
        }
    }

    // ���� ����
    DestroyItem();

    if (Particle)
    {
        FTimerHandle DestroyParticleTimerHandle;

        GetWorld()->GetTimerManager().SetTimer(
            DestroyParticleTimerHandle,
            [Particle]()
            {
                Particle->DestroyComponent();
            },
            2.0f,
            false
        );
    }
}

void AMeteorItem::BeginPlay()
{
    Super::BeginPlay();

    // ���� �� 0.1�� �ڿ� �����ϵ��� Ÿ�̸� ����
    GetWorld()->GetTimerManager().SetTimer(
        ExplosionTimerHandle,
        this,
        &AMeteorItem::Explode,
        ExplosionDelay,
        false
    );
    bHasExploded = true;
}