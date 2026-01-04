// cpp
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LF_AnimInsBase.generated.h"

UCLASS()
class LFGAME_API ULF_AnimInsBase : public UAnimInstance
{
    GENERATED_BODY()

public:
    // 在游戏线程上每帧调用（可用于需要访问 UObject 的更新）
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    // 如果引擎将 BlueprintThreadSafeUpdateAnimation 声明为 BlueprintNativeEvent，
    // 在 C++ 中实现其 _Implementation 来提供线程安全的动画线程逻辑
    virtual void BlueprintThreadSafeUpdateAnimation_Implementation(float DeltaSeconds);

    UFUNCTION(Blueprintable,,meta=(BlueprintThreadSafe))
    void UpdateVelocityData(float DeltaSeconds);

    UFUNCTION(Blueprintable,,meta=(BlueprintThreadSafe))
    void UpdateRotationData(float DeltaSeconds);

    UFUNCTION(Blueprintable,,meta=(BlueprintThreadSafe))
    void UpdateAccelerationData(float DeltaSeconds);
    
    UFUNCTION(Blueprintable,,meta=(BlueprintThreadSafe))
    void  UpdateLocationData(float DeltaSeconds);
    


    //=================Velocity==============================
    // 世界坐标速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
    FVector WorldVelocity;

    // XY 平面世界坐标速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
    FVector2D WorldVelocity2D;

    // 本地坐标速度 2D
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
    FVector2D LocalVelocity2D;

    // 当前是否有速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
    bool HasVelocity;
    //=================Rotation==============================
    // 世界坐标系旋转（三维）
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
    FRotator WorldRotation;

    // 世界坐标系二维旋转（主要关注Yaw偏航角）
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
    FRotator WorldRotation2D;

    // 本地坐标系二维旋转
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
    FRotator LocalRotation2D;

    // 当前是否正在旋转
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
    bool bIsRotating;

    //=================Acceleration==============================
    // 世界坐标加速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration", meta = (AllowPrivateAccess = "true"))
    FVector WorldAcceleration;

    // XY平面世界坐标加速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration", meta = (AllowPrivateAccess = "true"))
    FVector2D WorldAcceleration2D;

    // 本地坐标加速度2D
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration", meta = (AllowPrivateAccess = "true"))
    FVector2D LocalAcceleration2D;

    // 当前是否正在加速
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration", meta = (AllowPrivateAccess = "true"))
    bool bIsAccelerating;

    //=================Location==============================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location", meta = (AllowPrivateAccess = "true"))
    FVector DisplacementSpeed;
    
    //=================Other==============================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other", meta = (AllowPrivateAccess = "true"))
    bool bIsFirstUpdate = true;

private:


    FVector PreviousVelocity;
    FRotator PreviousRotation;
    
};

