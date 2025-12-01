// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/Loaders/UBVCSchemaLoaderJson.h"
#include "Schema/FBVCMADescriptionContainer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCSchemaLoaderJson() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCSchemaLoaderJson();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCSchemaLoaderJson_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescriptionContainer();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBVCSchemaLoaderJson Function LoadFromJsonString *************************
struct Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics
{
	struct BVCSchemaLoaderJson_eventLoadFromJsonString_Parms
	{
		FString Json;
		FBVCMADescriptionContainer OutContainer;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Schema" },
		{ "ModuleRelativePath", "Public/Schema/Loaders/UBVCSchemaLoaderJson.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Json_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Json;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutContainer;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_Json = { "Json", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaLoaderJson_eventLoadFromJsonString_Parms, Json), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Json_MetaData), NewProp_Json_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_OutContainer = { "OutContainer", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaLoaderJson_eventLoadFromJsonString_Parms, OutContainer), Z_Construct_UScriptStruct_FBVCMADescriptionContainer, METADATA_PARAMS(0, nullptr) }; // 3185162244
void Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCSchemaLoaderJson_eventLoadFromJsonString_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCSchemaLoaderJson_eventLoadFromJsonString_Parms), &Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_Json,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_OutContainer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCSchemaLoaderJson, nullptr, "LoadFromJsonString", Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::BVCSchemaLoaderJson_eventLoadFromJsonString_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::BVCSchemaLoaderJson_eventLoadFromJsonString_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCSchemaLoaderJson::execLoadFromJsonString)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Json);
	P_GET_STRUCT_REF(FBVCMADescriptionContainer,Z_Param_Out_OutContainer);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->LoadFromJsonString(Z_Param_Json,Z_Param_Out_OutContainer);
	P_NATIVE_END;
}
// ********** End Class UBVCSchemaLoaderJson Function LoadFromJsonString ***************************

// ********** Begin Class UBVCSchemaLoaderJson *****************************************************
void UBVCSchemaLoaderJson::StaticRegisterNativesUBVCSchemaLoaderJson()
{
	UClass* Class = UBVCSchemaLoaderJson::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "LoadFromJsonString", &UBVCSchemaLoaderJson::execLoadFromJsonString },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCSchemaLoaderJson;
UClass* UBVCSchemaLoaderJson::GetPrivateStaticClass()
{
	using TClass = UBVCSchemaLoaderJson;
	if (!Z_Registration_Info_UClass_UBVCSchemaLoaderJson.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCSchemaLoaderJson"),
			Z_Registration_Info_UClass_UBVCSchemaLoaderJson.InnerSingleton,
			StaticRegisterNativesUBVCSchemaLoaderJson,
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
	return Z_Registration_Info_UClass_UBVCSchemaLoaderJson.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCSchemaLoaderJson_NoRegister()
{
	return UBVCSchemaLoaderJson::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCSchemaLoaderJson_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Loads a Magritte-like schema catalog from a JSON string into FBVCMADescriptionContainer.\n * v1: strict field names; enums as strings (matching existing enum names).\n */" },
#endif
		{ "IncludePath", "Schema/Loaders/UBVCSchemaLoaderJson.h" },
		{ "ModuleRelativePath", "Public/Schema/Loaders/UBVCSchemaLoaderJson.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Loads a Magritte-like schema catalog from a JSON string into FBVCMADescriptionContainer.\nv1: strict field names; enums as strings (matching existing enum names)." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCSchemaLoaderJson_LoadFromJsonString, "LoadFromJsonString" }, // 2924950231
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCSchemaLoaderJson>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBVCSchemaLoaderJson_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCSchemaLoaderJson_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCSchemaLoaderJson_Statics::ClassParams = {
	&UBVCSchemaLoaderJson::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCSchemaLoaderJson_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCSchemaLoaderJson_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCSchemaLoaderJson()
{
	if (!Z_Registration_Info_UClass_UBVCSchemaLoaderJson.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCSchemaLoaderJson.OuterSingleton, Z_Construct_UClass_UBVCSchemaLoaderJson_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCSchemaLoaderJson.OuterSingleton;
}
UBVCSchemaLoaderJson::UBVCSchemaLoaderJson(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCSchemaLoaderJson);
UBVCSchemaLoaderJson::~UBVCSchemaLoaderJson() {}
// ********** End Class UBVCSchemaLoaderJson *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_Loaders_UBVCSchemaLoaderJson_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCSchemaLoaderJson, UBVCSchemaLoaderJson::StaticClass, TEXT("UBVCSchemaLoaderJson"), &Z_Registration_Info_UClass_UBVCSchemaLoaderJson, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCSchemaLoaderJson), 3127353215U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_Loaders_UBVCSchemaLoaderJson_h__Script_CatalystConnect_4076627945(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_Loaders_UBVCSchemaLoaderJson_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_Loaders_UBVCSchemaLoaderJson_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
