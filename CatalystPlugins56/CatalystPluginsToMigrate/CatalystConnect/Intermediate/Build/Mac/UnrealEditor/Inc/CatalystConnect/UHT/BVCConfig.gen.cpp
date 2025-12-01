// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/BVCConfig.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBVCConfig() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_EBVCQoS();
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCConfig();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBVCQoS *******************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBVCQoS;
static UEnum* EBVCQoS_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBVCQoS.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBVCQoS.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_EBVCQoS, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("EBVCQoS"));
	}
	return Z_Registration_Info_UEnum_EBVCQoS.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCQoS>()
{
	return EBVCQoS_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "High.Name", "EBVCQoS::High" },
		{ "Low.Name", "EBVCQoS::Low" },
		{ "Medium.Name", "EBVCQoS::Medium" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBVCQoS::High", (int64)EBVCQoS::High },
		{ "EBVCQoS::Medium", (int64)EBVCQoS::Medium },
		{ "EBVCQoS::Low", (int64)EBVCQoS::Low },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"EBVCQoS",
	"EBVCQoS",
	Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_EBVCQoS()
{
	if (!Z_Registration_Info_UEnum_EBVCQoS.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBVCQoS.InnerSingleton, Z_Construct_UEnum_CatalystConnect_EBVCQoS_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBVCQoS.InnerSingleton;
}
// ********** End Enum EBVCQoS *********************************************************************

// ********** Begin Enum EBVCValidationSetMode *****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBVCValidationSetMode;
static UEnum* EBVCValidationSetMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBVCValidationSetMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBVCValidationSetMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("EBVCValidationSetMode"));
	}
	return Z_Registration_Info_UEnum_EBVCValidationSetMode.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCValidationSetMode>()
{
	return EBVCValidationSetMode_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Deferred.Name", "EBVCValidationSetMode::Deferred" },
		{ "Eager.Name", "EBVCValidationSetMode::Eager" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
		{ "Off.Name", "EBVCValidationSetMode::Off" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBVCValidationSetMode::Off", (int64)EBVCValidationSetMode::Off },
		{ "EBVCValidationSetMode::Deferred", (int64)EBVCValidationSetMode::Deferred },
		{ "EBVCValidationSetMode::Eager", (int64)EBVCValidationSetMode::Eager },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"EBVCValidationSetMode",
	"EBVCValidationSetMode",
	Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode()
{
	if (!Z_Registration_Info_UEnum_EBVCValidationSetMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBVCValidationSetMode.InnerSingleton, Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBVCValidationSetMode.InnerSingleton;
}
// ********** End Enum EBVCValidationSetMode *******************************************************

// ********** Begin ScriptStruct FBVCConfig ********************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCConfig;
class UScriptStruct* FBVCConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCConfig, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCConfig"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCConfig.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCConfig_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProjectPrefix_MetaData[] = {
		{ "Category", "BVCConfig" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDeliverOnGameThread_MetaData[] = {
		{ "Category", "BVCConfig" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSetField_MetaData[] = {
		{ "Category", "BVCConfig" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClientValidationEnabled_MetaData[] = {
		{ "Category", "BVCConfig" },
		{ "ModuleRelativePath", "Public/Core/BVCConfig.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ProjectPrefix;
	static void NewProp_bDeliverOnGameThread_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDeliverOnGameThread;
	static const UECodeGen_Private::FBytePropertyParams NewProp_OnSetField_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_OnSetField;
	static void NewProp_bClientValidationEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClientValidationEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_ProjectPrefix = { "ProjectPrefix", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConfig, ProjectPrefix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProjectPrefix_MetaData), NewProp_ProjectPrefix_MetaData) };
void Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bDeliverOnGameThread_SetBit(void* Obj)
{
	((FBVCConfig*)Obj)->bDeliverOnGameThread = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bDeliverOnGameThread = { "bDeliverOnGameThread", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBVCConfig), &Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bDeliverOnGameThread_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDeliverOnGameThread_MetaData), NewProp_bDeliverOnGameThread_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_OnSetField_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_OnSetField = { "OnSetField", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConfig, OnSetField), Z_Construct_UEnum_CatalystConnect_EBVCValidationSetMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSetField_MetaData), NewProp_OnSetField_MetaData) }; // 1063972820
void Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bClientValidationEnabled_SetBit(void* Obj)
{
	((FBVCConfig*)Obj)->bClientValidationEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bClientValidationEnabled = { "bClientValidationEnabled", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBVCConfig), &Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bClientValidationEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClientValidationEnabled_MetaData), NewProp_bClientValidationEnabled_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_ProjectPrefix,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bDeliverOnGameThread,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_OnSetField_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_OnSetField,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConfig_Statics::NewProp_bClientValidationEnabled,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCConfig_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCConfig",
	Z_Construct_UScriptStruct_FBVCConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCConfig_Statics::PropPointers),
	sizeof(FBVCConfig),
	alignof(FBVCConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCConfig()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCConfig.InnerSingleton, Z_Construct_UScriptStruct_FBVCConfig_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCConfig.InnerSingleton;
}
// ********** End ScriptStruct FBVCConfig **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h__Script_CatalystConnect_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBVCQoS_StaticEnum, TEXT("EBVCQoS"), &Z_Registration_Info_UEnum_EBVCQoS, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 911422879U) },
		{ EBVCValidationSetMode_StaticEnum, TEXT("EBVCValidationSetMode"), &Z_Registration_Info_UEnum_EBVCValidationSetMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1063972820U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCConfig::StaticStruct, Z_Construct_UScriptStruct_FBVCConfig_Statics::NewStructOps, TEXT("BVCConfig"), &Z_Registration_Info_UScriptStruct_FBVCConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCConfig), 845929784U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h__Script_CatalystConnect_1446352606(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h__Script_CatalystConnect_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h__Script_CatalystConnect_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
