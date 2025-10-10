// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/FBVCMADescription.h"
#include "Schema/FBVCMAAttribute.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFBVCMADescription() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMAAttribute();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescription();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCMADescription *************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCMADescription;
class UScriptStruct* FBVCMADescription::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMADescription.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCMADescription.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCMADescription, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCMADescription"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCMADescription.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCMADescription_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassId_MetaData[] = {
		{ "Category", "BVCMADescription" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "BVCMADescription" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "Category", "BVCMADescription" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hash_MetaData[] = {
		{ "Category", "BVCMADescription" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Identifier_MetaData[] = {
		{ "Category", "BVCMADescription" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attributes_MetaData[] = {
		{ "Category", "BVCMADescription" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// id slot\n" },
#endif
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "id slot" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MethodNames_MetaData[] = {
		{ "Category", "BVCMADescription" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMADescription.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ClassId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Hash;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Identifier;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attributes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Attributes;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MethodNames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MethodNames;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCMADescription>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_ClassId = { "ClassId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, ClassId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassId_MetaData), NewProp_ClassId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Hash = { "Hash", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, Hash), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hash_MetaData), NewProp_Hash_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Identifier = { "Identifier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, Identifier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Identifier_MetaData), NewProp_Identifier_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Attributes_Inner = { "Attributes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBVCMAAttribute, METADATA_PARAMS(0, nullptr) }; // 3387388498
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Attributes = { "Attributes", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, Attributes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attributes_MetaData), NewProp_Attributes_MetaData) }; // 3387388498
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_MethodNames_Inner = { "MethodNames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_MethodNames = { "MethodNames", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMADescription, MethodNames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MethodNames_MetaData), NewProp_MethodNames_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCMADescription_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_ClassId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Version,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Hash,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Identifier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Attributes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_Attributes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_MethodNames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewProp_MethodNames,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMADescription_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCMADescription_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCMADescription",
	Z_Construct_UScriptStruct_FBVCMADescription_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMADescription_Statics::PropPointers),
	sizeof(FBVCMADescription),
	alignof(FBVCMADescription),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMADescription_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCMADescription_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescription()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMADescription.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCMADescription.InnerSingleton, Z_Construct_UScriptStruct_FBVCMADescription_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCMADescription.InnerSingleton;
}
// ********** End ScriptStruct FBVCMADescription ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescription_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCMADescription::StaticStruct, Z_Construct_UScriptStruct_FBVCMADescription_Statics::NewStructOps, TEXT("BVCMADescription"), &Z_Registration_Info_UScriptStruct_FBVCMADescription, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCMADescription), 2596472933U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescription_h__Script_CatalystConnect_4075497604(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescription_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMADescription_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
