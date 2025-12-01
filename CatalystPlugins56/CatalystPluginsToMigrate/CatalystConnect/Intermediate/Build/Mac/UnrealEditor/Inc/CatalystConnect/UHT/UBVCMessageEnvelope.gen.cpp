// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Transport/UBVCMessageEnvelope.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCMessageEnvelope() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMessageEnvelope();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCMessageEnvelope ***********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope;
class UScriptStruct* FBVCMessageEnvelope::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCMessageEnvelope, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCMessageEnvelope"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Encoding_MetaData[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Compression_MetaData[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimestampUtc_MetaData[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nonce_MetaData[] = {
		{ "ModuleRelativePath", "Public/Transport/UBVCMessageEnvelope.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Type;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Encoding;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Compression;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MessageId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TimestampUtc;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Nonce;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCMessageEnvelope>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMessageEnvelope, Type), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Encoding = { "Encoding", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMessageEnvelope, Encoding), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Encoding_MetaData), NewProp_Encoding_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Compression = { "Compression", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMessageEnvelope, Compression), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Compression_MetaData), NewProp_Compression_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_MessageId = { "MessageId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMessageEnvelope, MessageId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageId_MetaData), NewProp_MessageId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_TimestampUtc = { "TimestampUtc", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMessageEnvelope, TimestampUtc), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimestampUtc_MetaData), NewProp_TimestampUtc_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Nonce = { "Nonce", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMessageEnvelope, Nonce), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nonce_MetaData), NewProp_Nonce_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Encoding,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Compression,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_MessageId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_TimestampUtc,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewProp_Nonce,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCMessageEnvelope",
	Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::PropPointers),
	sizeof(FBVCMessageEnvelope),
	alignof(FBVCMessageEnvelope),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCMessageEnvelope()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope.InnerSingleton, Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope.InnerSingleton;
}
// ********** End ScriptStruct FBVCMessageEnvelope *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Transport_UBVCMessageEnvelope_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCMessageEnvelope::StaticStruct, Z_Construct_UScriptStruct_FBVCMessageEnvelope_Statics::NewStructOps, TEXT("BVCMessageEnvelope"), &Z_Registration_Info_UScriptStruct_FBVCMessageEnvelope, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCMessageEnvelope), 1351277959U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Transport_UBVCMessageEnvelope_h__Script_CatalystConnect_719799824(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Transport_UBVCMessageEnvelope_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Transport_UBVCMessageEnvelope_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
