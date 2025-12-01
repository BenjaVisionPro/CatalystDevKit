// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Runtime/UBVCSubscriptionHandle.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCSubscriptionHandle() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCSubscriptionHandle();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCSubscriptionHandle ********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle;
class UScriptStruct* FBVCSubscriptionHandle::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCSubscriptionHandle, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCSubscriptionHandle"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCSubscriptionHandle.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SubId_MetaData[] = {
		{ "Category", "BVCSubscriptionHandle" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCSubscriptionHandle.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FInt64PropertyParams NewProp_SubId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCSubscriptionHandle>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::NewProp_SubId = { "SubId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCSubscriptionHandle, SubId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SubId_MetaData), NewProp_SubId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::NewProp_SubId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCSubscriptionHandle",
	Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::PropPointers),
	sizeof(FBVCSubscriptionHandle),
	alignof(FBVCSubscriptionHandle),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCSubscriptionHandle()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle.InnerSingleton, Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle.InnerSingleton;
}
// ********** End ScriptStruct FBVCSubscriptionHandle **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCSubscriptionHandle_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCSubscriptionHandle::StaticStruct, Z_Construct_UScriptStruct_FBVCSubscriptionHandle_Statics::NewStructOps, TEXT("BVCSubscriptionHandle"), &Z_Registration_Info_UScriptStruct_FBVCSubscriptionHandle, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCSubscriptionHandle), 3305791878U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCSubscriptionHandle_h__Script_CatalystConnect_2927449414(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCSubscriptionHandle_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCSubscriptionHandle_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
