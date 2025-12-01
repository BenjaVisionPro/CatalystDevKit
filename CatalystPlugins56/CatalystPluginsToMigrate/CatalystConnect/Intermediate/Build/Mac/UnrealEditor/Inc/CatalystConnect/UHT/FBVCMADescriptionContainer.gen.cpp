// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/FBVCMADescriptionContainer.h"
#include "Schema/FBVCMADescription.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFBVCMADescriptionContainer() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescription();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescriptionContainer();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCMADescriptionContainer ****************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer;
class UScriptStruct* FBVCMADescriptionContainer::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCMADescriptionContainer, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCMADescriptionContainer"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescriptionContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CatalogId_MetaData[] = {
		{ "Category", "BVCMADescriptionContainer" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescriptionContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "Category", "BVCMADescriptionContainer" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescriptionContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hash_MetaData[] = {
		{ "Category", "BVCMADescriptionContainer" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescriptionContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Descriptions_MetaData[] = {
		{ "Category", "BVCMADescriptionContainer" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescriptionContainer.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_CatalogId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Hash;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Descriptions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Descriptions;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCMADescriptionContainer>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_CatalogId = { "CatalogId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescriptionContainer, CatalogId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CatalogId_MetaData), NewProp_CatalogId_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescriptionContainer, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Hash = { "Hash", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescriptionContainer, Hash), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hash_MetaData), NewProp_Hash_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Descriptions_Inner = { "Descriptions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBVCMADescription, METADATA_PARAMS(0, nullptr) }; // 2596472933
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Descriptions = { "Descriptions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescriptionContainer, Descriptions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Descriptions_MetaData), NewProp_Descriptions_MetaData) }; // 2596472933
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_CatalogId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Version,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Hash,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Descriptions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewProp_Descriptions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCMADescriptionContainer",
	Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::PropPointers),
	sizeof(FBVCMADescriptionContainer),
	alignof(FBVCMADescriptionContainer),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescriptionContainer()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer.InnerSingleton, Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer.InnerSingleton;
}
// ********** End ScriptStruct FBVCMADescriptionContainer ******************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescriptionContainer_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCMADescriptionContainer::StaticStruct, Z_Construct_UScriptStruct_FBVCMADescriptionContainer_Statics::NewStructOps, TEXT("BVCMADescriptionContainer"), &Z_Registration_Info_UScriptStruct_FBVCMADescriptionContainer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCMADescriptionContainer), 3185162244U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescriptionContainer_h__Script_CatalystConnect_906257568(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescriptionContainer_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescriptionContainer_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
