// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Runtime/UBVCRemoteObjectSpace.h"
#include "Runtime/UBVCSubscriptionHandle.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCRemoteObjectSpace() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObjectSpace();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObjectSpace_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCSubscriptionHandle();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBVCRemoteObjectSpace Function Subscribe *********************************
struct Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics
{
	struct BVCRemoteObjectSpace_eventSubscribe_Parms
	{
		TArray<FString> Classes;
		FName Topic;
		bool bDeliverOnGameThread;
		FBVCSubscriptionHandle ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|ObjectSpace" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObjectSpace.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Classes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Classes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Classes;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Topic;
	static void NewProp_bDeliverOnGameThread_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDeliverOnGameThread;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_Classes_Inner = { "Classes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_Classes = { "Classes", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObjectSpace_eventSubscribe_Parms, Classes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Classes_MetaData), NewProp_Classes_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_Topic = { "Topic", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObjectSpace_eventSubscribe_Parms, Topic), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_bDeliverOnGameThread_SetBit(void* Obj)
{
	((BVCRemoteObjectSpace_eventSubscribe_Parms*)Obj)->bDeliverOnGameThread = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_bDeliverOnGameThread = { "bDeliverOnGameThread", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCRemoteObjectSpace_eventSubscribe_Parms), &Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_bDeliverOnGameThread_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObjectSpace_eventSubscribe_Parms, ReturnValue), Z_Construct_UScriptStruct_FBVCSubscriptionHandle, METADATA_PARAMS(0, nullptr) }; // 3305791878
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_Classes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_Classes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_Topic,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_bDeliverOnGameThread,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCRemoteObjectSpace, nullptr, "Subscribe", Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::BVCRemoteObjectSpace_eventSubscribe_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::BVCRemoteObjectSpace_eventSubscribe_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCRemoteObjectSpace::execSubscribe)
{
	P_GET_TARRAY_REF(FString,Z_Param_Out_Classes);
	P_GET_PROPERTY(FNameProperty,Z_Param_Topic);
	P_GET_UBOOL(Z_Param_bDeliverOnGameThread);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBVCSubscriptionHandle*)Z_Param__Result=P_THIS->Subscribe(Z_Param_Out_Classes,Z_Param_Topic,Z_Param_bDeliverOnGameThread);
	P_NATIVE_END;
}
// ********** End Class UBVCRemoteObjectSpace Function Subscribe ***********************************

// ********** Begin Class UBVCRemoteObjectSpace Function Unsubscribe *******************************
struct Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics
{
	struct BVCRemoteObjectSpace_eventUnsubscribe_Parms
	{
		FBVCSubscriptionHandle Handle;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|ObjectSpace" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObjectSpace.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Handle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::NewProp_Handle = { "Handle", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObjectSpace_eventUnsubscribe_Parms, Handle), Z_Construct_UScriptStruct_FBVCSubscriptionHandle, METADATA_PARAMS(0, nullptr) }; // 3305791878
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::NewProp_Handle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCRemoteObjectSpace, nullptr, "Unsubscribe", Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::BVCRemoteObjectSpace_eventUnsubscribe_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::BVCRemoteObjectSpace_eventUnsubscribe_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCRemoteObjectSpace::execUnsubscribe)
{
	P_GET_STRUCT(FBVCSubscriptionHandle,Z_Param_Handle);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Unsubscribe(Z_Param_Handle);
	P_NATIVE_END;
}
// ********** End Class UBVCRemoteObjectSpace Function Unsubscribe *********************************

// ********** Begin Class UBVCRemoteObjectSpace ****************************************************
void UBVCRemoteObjectSpace::StaticRegisterNativesUBVCRemoteObjectSpace()
{
	UClass* Class = UBVCRemoteObjectSpace::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Subscribe", &UBVCRemoteObjectSpace::execSubscribe },
		{ "Unsubscribe", &UBVCRemoteObjectSpace::execUnsubscribe },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCRemoteObjectSpace;
UClass* UBVCRemoteObjectSpace::GetPrivateStaticClass()
{
	using TClass = UBVCRemoteObjectSpace;
	if (!Z_Registration_Info_UClass_UBVCRemoteObjectSpace.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCRemoteObjectSpace"),
			Z_Registration_Info_UClass_UBVCRemoteObjectSpace.InnerSingleton,
			StaticRegisterNativesUBVCRemoteObjectSpace,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UBVCRemoteObjectSpace.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCRemoteObjectSpace_NoRegister()
{
	return UBVCRemoteObjectSpace::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCRemoteObjectSpace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * UBVCRemoteObjectSpace\n * Root coordinator for remote model subscriptions and dispatch.\n * (Lightweight for v1: just manages subscription bookkeeping.)\n */" },
#endif
		{ "IncludePath", "Runtime/UBVCRemoteObjectSpace.h" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObjectSpace.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UBVCRemoteObjectSpace\nRoot coordinator for remote model subscriptions and dispatch.\n(Lightweight for v1: just manages subscription bookkeeping.)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastSubId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObjectSpace.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FInt64PropertyParams NewProp_LastSubId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCRemoteObjectSpace_Subscribe, "Subscribe" }, // 1889880520
		{ &Z_Construct_UFunction_UBVCRemoteObjectSpace_Unsubscribe, "Unsubscribe" }, // 4235373206
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCRemoteObjectSpace>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::NewProp_LastSubId = { "LastSubId", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCRemoteObjectSpace, LastSubId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastSubId_MetaData), NewProp_LastSubId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::NewProp_LastSubId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::ClassParams = {
	&UBVCRemoteObjectSpace::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCRemoteObjectSpace()
{
	if (!Z_Registration_Info_UClass_UBVCRemoteObjectSpace.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCRemoteObjectSpace.OuterSingleton, Z_Construct_UClass_UBVCRemoteObjectSpace_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCRemoteObjectSpace.OuterSingleton;
}
UBVCRemoteObjectSpace::UBVCRemoteObjectSpace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCRemoteObjectSpace);
UBVCRemoteObjectSpace::~UBVCRemoteObjectSpace() {}
// ********** End Class UBVCRemoteObjectSpace ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCRemoteObjectSpace, UBVCRemoteObjectSpace::StaticClass, TEXT("UBVCRemoteObjectSpace"), &Z_Registration_Info_UClass_UBVCRemoteObjectSpace, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCRemoteObjectSpace), 1503632969U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h__Script_CatalystConnect_474025877(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
