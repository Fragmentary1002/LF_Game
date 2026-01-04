// cpp
#include "LF_AnimInsBase.h"

void ULF_AnimInsBase::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // 在这里执行需要在游戏线程上的更新（读取/修改 UObjects、调用组件等）。
    // 如果需要把部分工作移到动画线程，确保该工作是线程安全的并由
    // BlueprintThreadSafeUpdateAnimation_Implementation 处理，或通过缓冲/缓存机制传递数据。
}

void ULF_AnimInsBase::BlueprintThreadSafeUpdateAnimation_Implementation(float DeltaSeconds)
{
    if (DeltaSeconds <= 0.0f)
    {
        return;
    }
    UpdateRotationData(DeltaSeconds);
    UpdateVelocityData(DeltaSeconds);
    UpdateAccelerationData(DeltaSeconds);
    UpdateLocationData(DeltaSeconds);
    // 保存当前帧数据供下一帧使用
    PreviousVelocity = WorldVelocity;
    PreviousRotation = WorldRotation;
    bIsFirstUpdate = false;
}


void ULF_AnimInsBase::UpdateVelocityData(float DeltaSeconds)
{
    AActor* Owner = TryGetPawnOwner();
    if (!Owner) return;
    
    // 获取世界坐标系速度[1](@ref)
    WorldVelocity = Owner->GetVelocity();
    
    // 计算XY平面速度
    WorldVelocity2D = FVector2D(WorldVelocity.X, WorldVelocity.Y);
    
    // 计算本地坐标系速度
    FVector LocalVelocity = Owner->GetActorTransform().InverseTransformVector(WorldVelocity);
    LocalVelocity2D = FVector2D(LocalVelocity.X, LocalVelocity.Y);
    
    // 判断是否有速度
    HasVelocity = !WorldVelocity.IsNearlyZero(1.0f); // 1cm/s阈值
}
void ULF_AnimInsBase::UpdateRotationData(float DeltaSeconds)
{
    AActor* Owner = TryGetPawnOwner();
    if (!Owner) return;
    
    // 获取世界坐标系旋转[6](@ref)
    WorldRotation = Owner->GetActorRotation();
    
    // 二维旋转（主要关注Yaw，Pitch和Roll设为0）
    WorldRotation2D = FRotator(0.f, WorldRotation.Yaw, 0.f);
    
    // 本地坐标系二维旋转（如果需要相对于父组件的旋转）
    if (USceneComponent* RootComp = Owner->GetRootComponent())
    {
        if (RootComp->GetAttachParent())
        {
            FRotator WorldRot = RootComp->GetComponentRotation();
            FRotator ParentWorldRot = RootComp->GetAttachParent()->GetComponentRotation();
            LocalRotation2D = (WorldRot - ParentWorldRot).GetNormalized();
            LocalRotation2D.Pitch = 0.f;
            LocalRotation2D.Roll = 0.f;
        }
        else
        {
            LocalRotation2D = WorldRotation2D;
        }
    }
    
    // 判断是否在旋转（通过角速度或旋转变化）
    bIsRotating = !WorldRotation.Equals(PreviousRotation, 0.1f); // 0.1度阈值
}
void ULF_AnimInsBase::UpdateAccelerationData(float DeltaSeconds)
{
    if (DeltaSeconds < KINDA_SMALL_NUMBER) return;
    
    // 计算加速度：a = (v_current - v_previous) / Δt[9,11](@ref)
    WorldAcceleration = (WorldVelocity - PreviousVelocity) / DeltaSeconds;
    
    // XY平面加速度
    WorldAcceleration2D = FVector2D(WorldAcceleration.X, WorldAcceleration.Y);
    
    // 本地坐标系加速度
    AActor* Owner = TryGetPawnOwner();
    if (Owner)
    {
        FVector LocalAcceleration = Owner->GetActorTransform().InverseTransformVector(WorldAcceleration);
        LocalAcceleration2D = FVector2D(LocalAcceleration.X, LocalAcceleration.Y);
    }
    
    // 判断是否在加速
    bIsAccelerating = !WorldAcceleration.IsNearlyZero(10.0f); // 10cm/s²阈值
}
void ULF_AnimInsBase::UpdateLocationData(float DeltaSeconds)
{
    FVector CurrentLocation = GetOwningActor()->GetActorLocation();
    DisplacementSpeed =bIsFirstUpdate? CurrentLocation - PreviousVelocity:FVector(0,0,0);
}