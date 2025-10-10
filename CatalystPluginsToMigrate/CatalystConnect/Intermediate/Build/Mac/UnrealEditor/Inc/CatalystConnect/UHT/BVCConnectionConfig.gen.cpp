// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Connection/BVCConnectionConfig.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBVCConnectionConfig() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCConnectionConfig();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCConnectionConfig **********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCConnectionConfig;
class UScriptStruct* FBVCConnectionConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCConnectionConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCConnectionConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCConnectionConfig, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCConnectionConfig"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCConnectionConfig.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Connection/BVCConnectionConfig.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SessionName_MetaData[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unique ID for this session (used as key in the subsystem). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/BVCConnectionConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unique ID for this session (used as key in the subsystem)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayLabel_MetaData[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Display label (optional, UI only). If empty, defaults to SessionName. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/BVCConnectionConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Display label (optional, UI only). If empty, defaults to SessionName." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Url_MetaData[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Endpoint URL (ws://, wss://, etc.). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/BVCConnectionConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Endpoint URL (ws://, wss://, etc.)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxMessageBytes_MetaData[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max reassembled message size in bytes. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/BVCConnectionConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max reassembled message size in bytes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FragmentTimeoutSeconds_MetaData[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fragment timeout for reassembly, seconds. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/BVCConnectionConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fragment timeout for reassembly, seconds." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_SessionName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayLabel;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Url;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxMessageBytes;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_FragmentTimeoutSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCConnectionConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_SessionName = { "SessionName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConnectionConfig, SessionName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SessionName_MetaData), NewProp_SessionName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_DisplayLabel = { "DisplayLabel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConnectionConfig, DisplayLabel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayLabel_MetaData), NewProp_DisplayLabel_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_Url = { "Url", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConnectionConfig, Url), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Url_MetaData), NewProp_Url_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_MaxMessageBytes = { "MaxMessageBytes", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConnectionConfig, MaxMessageBytes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxMessageBytes_MetaData), NewProp_MaxMessageBytes_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_FragmentTimeoutSeconds = { "FragmentTimeoutSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCConnectionConfig, FragmentTimeoutSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FragmentTimeoutSeconds_MetaData), NewProp_FragmentTimeoutSeconds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_SessionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_DisplayLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_Url,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_MaxMessageBytes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewProp_FragmentTimeoutSeconds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCConnectionConfig",
	Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::PropPointers),
	sizeof(FBVCConnectionConfig),
	alignof(FBVCConnectionConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCConnectionConfig()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCConnectionConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCConnectionConfig.InnerSingleton, Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCConnectionConfig.InnerSingleton;
}
// ********** End ScriptStruct FBVCConnectionConfig ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_BVCConnectionConfig_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCConnectionConfig::StaticStruct, Z_Construct_UScriptStruct_FBVCConnectionConfig_Statics::NewStructOps, TEXT("BVCConnectionConfig"), &Z_Registration_Info_UScriptStruct_FBVCConnectionConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCConnectionConfig), 3760486832U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_BVCConnectionConfig_h__Script_CatalystConnect_294241415(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_BVCConnectionConfig_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_BVCConnectionConfig_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
