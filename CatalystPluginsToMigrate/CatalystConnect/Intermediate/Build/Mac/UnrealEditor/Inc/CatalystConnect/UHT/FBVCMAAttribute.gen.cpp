// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/FBVCMAAttribute.h"
#include "Schema/FBVCMAValidatorSpec.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFBVCMAAttribute() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_EBVCMAKind();
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMAAttribute();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMAValidatorSpec();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBVCMAKind ****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBVCMAKind;
static UEnum* EBVCMAKind_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBVCMAKind.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBVCMAKind.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_EBVCMAKind, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("EBVCMAKind"));
	}
	return Z_Registration_Info_UEnum_EBVCMAKind.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCMAKind>()
{
	return EBVCMAKind_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Enum.Name", "EBVCMAKind::Enum" },
		{ "Map.Name", "EBVCMAKind::Map" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
		{ "Scalar.Name", "EBVCMAKind::Scalar" },
		{ "ToMany.Name", "EBVCMAKind::ToMany" },
		{ "ToOne.Name", "EBVCMAKind::ToOne" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBVCMAKind::Scalar", (int64)EBVCMAKind::Scalar },
		{ "EBVCMAKind::ToOne", (int64)EBVCMAKind::ToOne },
		{ "EBVCMAKind::ToMany", (int64)EBVCMAKind::ToMany },
		{ "EBVCMAKind::Enum", (int64)EBVCMAKind::Enum },
		{ "EBVCMAKind::Map", (int64)EBVCMAKind::Map },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"EBVCMAKind",
	"EBVCMAKind",
	Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_EBVCMAKind()
{
	if (!Z_Registration_Info_UEnum_EBVCMAKind.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBVCMAKind.InnerSingleton, Z_Construct_UEnum_CatalystConnect_EBVCMAKind_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBVCMAKind.InnerSingleton;
}
// ********** End Enum EBVCMAKind ******************************************************************

// ********** Begin Enum EBVCMAScalarType **********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBVCMAScalarType;
static UEnum* EBVCMAScalarType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBVCMAScalarType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBVCMAScalarType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("EBVCMAScalarType"));
	}
	return Z_Registration_Info_UEnum_EBVCMAScalarType.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCMAScalarType>()
{
	return EBVCMAScalarType_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Bool.Name", "EBVCMAScalarType::Bool" },
		{ "ByteArray.Name", "EBVCMAScalarType::ByteArray" },
		{ "DateTime.Name", "EBVCMAScalarType::DateTime" },
		{ "Float32.Name", "EBVCMAScalarType::Float32" },
		{ "Float64.Name", "EBVCMAScalarType::Float64" },
		{ "Guid.Name", "EBVCMAScalarType::Guid" },
		{ "Int32.Name", "EBVCMAScalarType::Int32" },
		{ "Int64.Name", "EBVCMAScalarType::Int64" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
		{ "Name.Name", "EBVCMAScalarType::Name" },
		{ "None.Name", "EBVCMAScalarType::None" },
		{ "String.Name", "EBVCMAScalarType::String" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBVCMAScalarType::None", (int64)EBVCMAScalarType::None },
		{ "EBVCMAScalarType::Bool", (int64)EBVCMAScalarType::Bool },
		{ "EBVCMAScalarType::Int32", (int64)EBVCMAScalarType::Int32 },
		{ "EBVCMAScalarType::Int64", (int64)EBVCMAScalarType::Int64 },
		{ "EBVCMAScalarType::Float32", (int64)EBVCMAScalarType::Float32 },
		{ "EBVCMAScalarType::Float64", (int64)EBVCMAScalarType::Float64 },
		{ "EBVCMAScalarType::String", (int64)EBVCMAScalarType::String },
		{ "EBVCMAScalarType::Name", (int64)EBVCMAScalarType::Name },
		{ "EBVCMAScalarType::Guid", (int64)EBVCMAScalarType::Guid },
		{ "EBVCMAScalarType::ByteArray", (int64)EBVCMAScalarType::ByteArray },
		{ "EBVCMAScalarType::DateTime", (int64)EBVCMAScalarType::DateTime },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"EBVCMAScalarType",
	"EBVCMAScalarType",
	Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType()
{
	if (!Z_Registration_Info_UEnum_EBVCMAScalarType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBVCMAScalarType.InnerSingleton, Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBVCMAScalarType.InnerSingleton;
}
// ********** End Enum EBVCMAScalarType ************************************************************

// ********** Begin ScriptStruct FBVCMAAttribute ***************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCMAAttribute;
class UScriptStruct* FBVCMAAttribute::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMAAttribute.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCMAAttribute.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCMAAttribute, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCMAAttribute"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCMAAttribute.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCMAAttribute_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Kind_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScalarType_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bNullable_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EpsilonAbs_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EpsilonRel_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnumSymbols_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Label_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Help_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValueJson_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Validators_MetaData[] = {
		{ "Category", "BVCMAAttribute" },
		{ "ModuleRelativePath", "Public/Schema/FBVCMAAttribute.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Kind_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Kind;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ScalarType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ScalarType;
	static void NewProp_bNullable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNullable;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_EpsilonAbs;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_EpsilonRel;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EnumSymbols_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_EnumSymbols;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Label;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Help;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValueJson;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Validators_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Validators;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCMAAttribute>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Kind_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Kind = { "Kind", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, Kind), Z_Construct_UEnum_CatalystConnect_EBVCMAKind, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Kind_MetaData), NewProp_Kind_MetaData) }; // 2824787525
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_ScalarType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_ScalarType = { "ScalarType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, ScalarType), Z_Construct_UEnum_CatalystConnect_EBVCMAScalarType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScalarType_MetaData), NewProp_ScalarType_MetaData) }; // 765371237
void Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_bNullable_SetBit(void* Obj)
{
	((FBVCMAAttribute*)Obj)->bNullable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_bNullable = { "bNullable", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBVCMAAttribute), &Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_bNullable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bNullable_MetaData), NewProp_bNullable_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EpsilonAbs = { "EpsilonAbs", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, EpsilonAbs), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EpsilonAbs_MetaData), NewProp_EpsilonAbs_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EpsilonRel = { "EpsilonRel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, EpsilonRel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EpsilonRel_MetaData), NewProp_EpsilonRel_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EnumSymbols_Inner = { "EnumSymbols", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EnumSymbols = { "EnumSymbols", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, EnumSymbols), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnumSymbols_MetaData), NewProp_EnumSymbols_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Label = { "Label", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, Label), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Label_MetaData), NewProp_Label_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Help = { "Help", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, Help), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Help_MetaData), NewProp_Help_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_DefaultValueJson = { "DefaultValueJson", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, DefaultValueJson), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValueJson_MetaData), NewProp_DefaultValueJson_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Validators_Inner = { "Validators", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBVCMAValidatorSpec, METADATA_PARAMS(0, nullptr) }; // 291496713
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Validators = { "Validators", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCMAAttribute, Validators), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Validators_MetaData), NewProp_Validators_MetaData) }; // 291496713
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Kind_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Kind,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_ScalarType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_ScalarType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_bNullable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EpsilonAbs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EpsilonRel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EnumSymbols_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_EnumSymbols,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Label,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Help,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_DefaultValueJson,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Validators_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewProp_Validators,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCMAAttribute",
	Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::PropPointers),
	sizeof(FBVCMAAttribute),
	alignof(FBVCMAAttribute),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCMAAttribute()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCMAAttribute.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCMAAttribute.InnerSingleton, Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCMAAttribute.InnerSingleton;
}
// ********** End ScriptStruct FBVCMAAttribute *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h__Script_CatalystConnect_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBVCMAKind_StaticEnum, TEXT("EBVCMAKind"), &Z_Registration_Info_UEnum_EBVCMAKind, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2824787525U) },
		{ EBVCMAScalarType_StaticEnum, TEXT("EBVCMAScalarType"), &Z_Registration_Info_UEnum_EBVCMAScalarType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 765371237U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCMAAttribute::StaticStruct, Z_Construct_UScriptStruct_FBVCMAAttribute_Statics::NewStructOps, TEXT("BVCMAAttribute"), &Z_Registration_Info_UScriptStruct_FBVCMAAttribute, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCMAAttribute), 3387388498U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h__Script_CatalystConnect_2869908647(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h__Script_CatalystConnect_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h__Script_CatalystConnect_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
