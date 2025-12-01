// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/FBVCMAValidatorSpec.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFBVCMAValidatorSpec() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMAValidatorSpec();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBVCMAValidatorType *******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBVCMAValidatorType;
static UEnum* EBVCMAValidatorType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBVCMAValidatorType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBVCMAValidatorType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("EBVCMAValidatorType"));
	}
	return Z_Registration_Info_UEnum_EBVCMAValidatorType.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCMAValidatorType>()
{
	return EBVCMAValidatorType_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CrossField.Name", "EBVCMAValidatorType::CrossField" },
		{ "CustomRef.Name", "EBVCMAValidatorType::CustomRef" },
		{ "Enumeration.Name", "EBVCMAValidatorType::Enumeration" },
		{ "Length.Name", "EBVCMAValidatorType::Length" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
		{ "Range.Name", "EBVCMAValidatorType::Range" },
		{ "Regex.Name", "EBVCMAValidatorType::Regex" },
		{ "Required.Name", "EBVCMAValidatorType::Required" },
		{ "UniqueInArray.Name", "EBVCMAValidatorType::UniqueInArray" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBVCMAValidatorType::Required", (int64)EBVCMAValidatorType::Required },
		{ "EBVCMAValidatorType::Length", (int64)EBVCMAValidatorType::Length },
		{ "EBVCMAValidatorType::Range", (int64)EBVCMAValidatorType::Range },
		{ "EBVCMAValidatorType::Regex", (int64)EBVCMAValidatorType::Regex },
		{ "EBVCMAValidatorType::Enumeration", (int64)EBVCMAValidatorType::Enumeration },
		{ "EBVCMAValidatorType::CrossField", (int64)EBVCMAValidatorType::CrossField },
		{ "EBVCMAValidatorType::UniqueInArray", (int64)EBVCMAValidatorType::UniqueInArray },
		{ "EBVCMAValidatorType::CustomRef", (int64)EBVCMAValidatorType::CustomRef },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"EBVCMAValidatorType",
	"EBVCMAValidatorType",
	Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType()
{
	if (!Z_Registration_Info_UEnum_EBVCMAValidatorType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBVCMAValidatorType.InnerSingleton, Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBVCMAValidatorType.InnerSingleton;
}
// ********** End Enum EBVCMAValidatorType *********************************************************

// ********** Begin ScriptStruct FBVCMAValidatorSpec ***********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec;
class UScriptStruct* FBVCMAValidatorSpec::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCMAValidatorSpec, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCMAValidatorSpec"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "BVCMAValidatorSpec" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArgsJson_MetaData[] = {
		{ "Category", "BVCMAValidatorSpec" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageCode_MetaData[] = {
		{ "Category", "BVCMAValidatorSpec" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "Category", "BVCMAValidatorSpec" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WhenExpr_MetaData[] = {
		{ "Category", "BVCMAValidatorSpec" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAValidatorSpec.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ArgsJson;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MessageCode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FStrPropertyParams NewProp_WhenExpr;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCMAValidatorSpec>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAValidatorSpec, Type), Z_Construct_UEnum_CatalystConnect_EBVCMAValidatorType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 221131689
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_ArgsJson = { "ArgsJson", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAValidatorSpec, ArgsJson), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArgsJson_MetaData), NewProp_ArgsJson_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_MessageCode = { "MessageCode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAValidatorSpec, MessageCode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageCode_MetaData), NewProp_MessageCode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAValidatorSpec, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_WhenExpr = { "WhenExpr", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAValidatorSpec, WhenExpr), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WhenExpr_MetaData), NewProp_WhenExpr_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_ArgsJson,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_MessageCode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_Message,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewProp_WhenExpr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCMAValidatorSpec",
	Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::PropPointers),
	sizeof(FBVCMAValidatorSpec),
	alignof(FBVCMAValidatorSpec),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCMAValidatorSpec()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec.InnerSingleton, Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec.InnerSingleton;
}
// ********** End ScriptStruct FBVCMAValidatorSpec *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h__Script_CatalystConnect_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBVCMAValidatorType_StaticEnum, TEXT("EBVCMAValidatorType"), &Z_Registration_Info_UEnum_EBVCMAValidatorType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 221131689U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCMAValidatorSpec::StaticStruct, Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics::NewStructOps, TEXT("BVCMAValidatorSpec"), &Z_Registration_Info_UScriptStruct_FBVCMAValidatorSpec, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCMAValidatorSpec), 291496713U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h__Script_CatalystConnect_3250875789(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h__Script_CatalystConnect_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h__Script_CatalystConnect_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
