// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/BVCValue.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBVCValue() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_EBVCValueType();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCValue();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBVCValueType *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBVCValueType;
static UEnum* EBVCValueType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBVCValueType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBVCValueType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_EBVCValueType, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("EBVCValueType"));
	}
	return Z_Registration_Info_UEnum_EBVCValueType.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCValueType>()
{
	return EBVCValueType_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Array.Name", "EBVCValueType::Array" },
		{ "Bool.Name", "EBVCValueType::Bool" },
		{ "ByteArray.Name", "EBVCValueType::ByteArray" },
		{ "Double.Name", "EBVCValueType::Double" },
		{ "EnumString.Name", "EBVCValueType::EnumString" },
		{ "Float.Name", "EBVCValueType::Float" },
		{ "Guid.Name", "EBVCValueType::Guid" },
		{ "Int32.Name", "EBVCValueType::Int32" },
		{ "Int64.Name", "EBVCValueType::Int64" },
		{ "Map.Name", "EBVCValueType::Map" },
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
		{ "Name.Name", "EBVCValueType::Name" },
		{ "None.Name", "EBVCValueType::None" },
		{ "String.Name", "EBVCValueType::String" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBVCValueType::None", (int64)EBVCValueType::None },
		{ "EBVCValueType::Bool", (int64)EBVCValueType::Bool },
		{ "EBVCValueType::Int32", (int64)EBVCValueType::Int32 },
		{ "EBVCValueType::Int64", (int64)EBVCValueType::Int64 },
		{ "EBVCValueType::Float", (int64)EBVCValueType::Float },
		{ "EBVCValueType::Double", (int64)EBVCValueType::Double },
		{ "EBVCValueType::String", (int64)EBVCValueType::String },
		{ "EBVCValueType::Name", (int64)EBVCValueType::Name },
		{ "EBVCValueType::Guid", (int64)EBVCValueType::Guid },
		{ "EBVCValueType::ByteArray", (int64)EBVCValueType::ByteArray },
		{ "EBVCValueType::Array", (int64)EBVCValueType::Array },
		{ "EBVCValueType::Map", (int64)EBVCValueType::Map },
		{ "EBVCValueType::EnumString", (int64)EBVCValueType::EnumString },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"EBVCValueType",
	"EBVCValueType",
	Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_EBVCValueType()
{
	if (!Z_Registration_Info_UEnum_EBVCValueType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBVCValueType.InnerSingleton, Z_Construct_UEnum_CatalystConnect_EBVCValueType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBVCValueType.InnerSingleton;
}
// ********** End Enum EBVCValueType ***************************************************************

// ********** Begin ScriptStruct FBVCValue *********************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCValue;
class UScriptStruct* FBVCValue::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCValue.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCValue.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCValue, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCValue"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCValue.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCValue_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bool_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Int32_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Int64_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Float_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Double_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_String_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Guid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ByteArray_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/BVCValue.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static void NewProp_Bool_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_Bool;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Int32;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Int64;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Float;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_Double;
	static const UECodeGen_Private::FStrPropertyParams NewProp_String;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Guid;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ByteArray_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ByteArray;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCValue>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Type), Z_Construct_UEnum_CatalystConnect_EBVCValueType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 3119893415
void Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Bool_SetBit(void* Obj)
{
	((FBVCValue*)Obj)->Bool = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Bool = { "Bool", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBVCValue), &Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Bool_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bool_MetaData), NewProp_Bool_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Int32 = { "Int32", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Int32), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Int32_MetaData), NewProp_Int32_MetaData) };
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Int64 = { "Int64", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Int64), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Int64_MetaData), NewProp_Int64_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Float = { "Float", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Float), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Float_MetaData), NewProp_Float_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Double = { "Double", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Double), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Double_MetaData), NewProp_Double_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_String = { "String", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, String), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_String_MetaData), NewProp_String_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Guid = { "Guid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, Guid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Guid_MetaData), NewProp_Guid_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_ByteArray_Inner = { "ByteArray", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_ByteArray = { "ByteArray", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValue, ByteArray), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ByteArray_MetaData), NewProp_ByteArray_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Bool,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Int32,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Int64,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Float,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Double,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_String,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_Guid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_ByteArray_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValue_Statics::NewProp_ByteArray,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCValue_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCValue",
	Z_Construct_UScriptStruct_FBVCValue_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCValue_Statics::PropPointers),
	sizeof(FBVCValue),
	alignof(FBVCValue),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCValue_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCValue_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCValue()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCValue.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCValue.InnerSingleton, Z_Construct_UScriptStruct_FBVCValue_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCValue.InnerSingleton;
}
// ********** End ScriptStruct FBVCValue ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h__Script_CatalystConnect_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBVCValueType_StaticEnum, TEXT("EBVCValueType"), &Z_Registration_Info_UEnum_EBVCValueType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3119893415U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCValue::StaticStruct, Z_Construct_UScriptStruct_FBVCValue_Statics::NewStructOps, TEXT("BVCValue"), &Z_Registration_Info_UScriptStruct_FBVCValue, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCValue), 1160158077U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h__Script_CatalystConnect_4228652498(TEXT("/Script/CatalystConnect"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h__Script_CatalystConnect_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h__Script_CatalystConnect_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
