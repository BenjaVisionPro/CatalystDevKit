// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Runtime/UBVCValidationEngine.h"
#include "Schema/FBVCMADescription.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCValidationEngine() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCValidationEngine();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCValidationEngine_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescription();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCValidationIssue();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCValidationIssue ***********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCValidationIssue;
class UScriptStruct* FBVCValidationIssue::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCValidationIssue.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCValidationIssue.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCValidationIssue, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCValidationIssue"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCValidationIssue.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCValidationIssue_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldPath_MetaData[] = {
		{ "Category", "BVCValidationIssue" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageCode_MetaData[] = {
		{ "Category", "BVCValidationIssue" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "Category", "BVCValidationIssue" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FieldPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MessageCode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCValidationIssue>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewProp_FieldPath = { "FieldPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValidationIssue, FieldPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldPath_MetaData), NewProp_FieldPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewProp_MessageCode = { "MessageCode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValidationIssue, MessageCode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageCode_MetaData), NewProp_MessageCode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCValidationIssue, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewProp_FieldPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewProp_MessageCode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCValidationIssue",
	Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::PropPointers),
	sizeof(FBVCValidationIssue),
	alignof(FBVCValidationIssue),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCValidationIssue()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCValidationIssue.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCValidationIssue.InnerSingleton, Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCValidationIssue.InnerSingleton;
}
// ********** End ScriptStruct FBVCValidationIssue *************************************************

// ********** Begin Class UBVCValidationEngine Function ValidateField ******************************
struct Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics
{
	struct BVCValidationEngine_eventValidateField_Parms
	{
		FBVCMADescription Description;
		FName Field;
		FString Value;
		TArray<FBVCValidationIssue> OutIssues;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Validation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Validate a single field against its Magritte description\n" },
#endif
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Validate a single field against its Magritte description" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Description;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Field;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Value;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutIssues_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutIssues;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCValidationEngine_eventValidateField_Parms, Description), Z_Construct_UScriptStruct_FBVCMADescription, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) }; // 2596472933
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_Field = { "Field", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCValidationEngine_eventValidateField_Parms, Field), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCValidationEngine_eventValidateField_Parms, Value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_OutIssues_Inner = { "OutIssues", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBVCValidationIssue, METADATA_PARAMS(0, nullptr) }; // 3975629669
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_OutIssues = { "OutIssues", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCValidationEngine_eventValidateField_Parms, OutIssues), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3975629669
void Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCValidationEngine_eventValidateField_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCValidationEngine_eventValidateField_Parms), &Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_Field,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_OutIssues_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_OutIssues,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCValidationEngine, nullptr, "ValidateField", Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::BVCValidationEngine_eventValidateField_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::BVCValidationEngine_eventValidateField_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCValidationEngine_ValidateField()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCValidationEngine_ValidateField_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCValidationEngine::execValidateField)
{
	P_GET_STRUCT_REF(FBVCMADescription,Z_Param_Out_Description);
	P_GET_PROPERTY(FNameProperty,Z_Param_Field);
	P_GET_PROPERTY(FStrProperty,Z_Param_Value);
	P_GET_TARRAY_REF(FBVCValidationIssue,Z_Param_Out_OutIssues);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ValidateField(Z_Param_Out_Description,Z_Param_Field,Z_Param_Value,Z_Param_Out_OutIssues);
	P_NATIVE_END;
}
// ********** End Class UBVCValidationEngine Function ValidateField ********************************

// ********** Begin Class UBVCValidationEngine Function ValidateObject *****************************
struct Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics
{
	struct BVCValidationEngine_eventValidateObject_Parms
	{
		FBVCMADescription Description;
		TArray<FBVCValidationIssue> OutIssues;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Validation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Validate all fields in an object (placeholder for now)\n" },
#endif
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Validate all fields in an object (placeholder for now)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Description;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutIssues_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutIssues;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCValidationEngine_eventValidateObject_Parms, Description), Z_Construct_UScriptStruct_FBVCMADescription, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) }; // 2596472933
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_OutIssues_Inner = { "OutIssues", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBVCValidationIssue, METADATA_PARAMS(0, nullptr) }; // 3975629669
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_OutIssues = { "OutIssues", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCValidationEngine_eventValidateObject_Parms, OutIssues), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3975629669
void Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCValidationEngine_eventValidateObject_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCValidationEngine_eventValidateObject_Parms), &Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_OutIssues_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_OutIssues,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCValidationEngine, nullptr, "ValidateObject", Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::BVCValidationEngine_eventValidateObject_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::BVCValidationEngine_eventValidateObject_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCValidationEngine_ValidateObject()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCValidationEngine_ValidateObject_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCValidationEngine::execValidateObject)
{
	P_GET_STRUCT_REF(FBVCMADescription,Z_Param_Out_Description);
	P_GET_TARRAY_REF(FBVCValidationIssue,Z_Param_Out_OutIssues);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ValidateObject(Z_Param_Out_Description,Z_Param_Out_OutIssues);
	P_NATIVE_END;
}
// ********** End Class UBVCValidationEngine Function ValidateObject *******************************

// ********** Begin Class UBVCValidationEngine *****************************************************
void UBVCValidationEngine::StaticRegisterNativesUBVCValidationEngine()
{
	UClass* Class = UBVCValidationEngine::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ValidateField", &UBVCValidationEngine::execValidateField },
		{ "ValidateObject", &UBVCValidationEngine::execValidateObject },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCValidationEngine;
UClass* UBVCValidationEngine::GetPrivateStaticClass()
{
	using TClass = UBVCValidationEngine;
	if (!Z_Registration_Info_UClass_UBVCValidationEngine.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCValidationEngine"),
			Z_Registration_Info_UClass_UBVCValidationEngine.InnerSingleton,
			StaticRegisterNativesUBVCValidationEngine,
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
	return Z_Registration_Info_UClass_UBVCValidationEngine.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCValidationEngine_NoRegister()
{
	return UBVCValidationEngine::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCValidationEngine_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Runtime/UBVCValidationEngine.h" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCValidationEngine.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCValidationEngine_ValidateField, "ValidateField" }, // 1278030971
		{ &Z_Construct_UFunction_UBVCValidationEngine_ValidateObject, "ValidateObject" }, // 1964437086
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCValidationEngine>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBVCValidationEngine_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCValidationEngine_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCValidationEngine_Statics::ClassParams = {
	&UBVCValidationEngine::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCValidationEngine_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCValidationEngine_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCValidationEngine()
{
	if (!Z_Registration_Info_UClass_UBVCValidationEngine.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCValidationEngine.OuterSingleton, Z_Construct_UClass_UBVCValidationEngine_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCValidationEngine.OuterSingleton;
}
UBVCValidationEngine::UBVCValidationEngine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCValidationEngine);
UBVCValidationEngine::~UBVCValidationEngine() {}
// ********** End Class UBVCValidationEngine *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCValidationIssue::StaticStruct, Z_Construct_UScriptStruct_FBVCValidationIssue_Statics::NewStructOps, TEXT("BVCValidationIssue"), &Z_Registration_Info_UScriptStruct_FBVCValidationIssue, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCValidationIssue), 3975629669U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCValidationEngine, UBVCValidationEngine::StaticClass, TEXT("UBVCValidationEngine"), &Z_Registration_Info_UClass_UBVCValidationEngine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCValidationEngine), 2846770309U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h__Script_CatalystConnect_3289596834(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h__Script_CatalystConnect_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
