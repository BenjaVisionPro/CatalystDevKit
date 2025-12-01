// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/UBVCSchemaRegistry.h"
#include "Schema/FBVCMADescription.h"
#include "Schema/FBVCMADescriptionContainer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCSchemaRegistry() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCSchemaRegistry();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCSchemaRegistry_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescription();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCMADescriptionContainer();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBVCSchemaRegistry Function FindByName ***********************************
struct Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics
{
	struct BVCSchemaRegistry_eventFindByName_Parms
	{
		FName ClassName;
		FBVCMADescription OutDescription;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Schema" },
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_ClassName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutDescription;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_ClassName = { "ClassName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaRegistry_eventFindByName_Parms, ClassName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_OutDescription = { "OutDescription", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaRegistry_eventFindByName_Parms, OutDescription), Z_Construct_UScriptStruct_FBVCMADescription, METADATA_PARAMS(0, nullptr) }; // 2596472933
void Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCSchemaRegistry_eventFindByName_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCSchemaRegistry_eventFindByName_Parms), &Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_ClassName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_OutDescription,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCSchemaRegistry, nullptr, "FindByName", Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::BVCSchemaRegistry_eventFindByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::BVCSchemaRegistry_eventFindByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCSchemaRegistry_FindByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCSchemaRegistry_FindByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCSchemaRegistry::execFindByName)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ClassName);
	P_GET_STRUCT_REF(FBVCMADescription,Z_Param_Out_OutDescription);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->FindByName(Z_Param_ClassName,Z_Param_Out_OutDescription);
	P_NATIVE_END;
}
// ********** End Class UBVCSchemaRegistry Function FindByName *************************************

// ********** Begin Class UBVCSchemaRegistry Function RegisterCatalog ******************************
struct Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics
{
	struct BVCSchemaRegistry_eventRegisterCatalog_Parms
	{
		FBVCMADescriptionContainer InContainer;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Schema" },
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InContainer_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InContainer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::NewProp_InContainer = { "InContainer", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaRegistry_eventRegisterCatalog_Parms, InContainer), Z_Construct_UScriptStruct_FBVCMADescriptionContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InContainer_MetaData), NewProp_InContainer_MetaData) }; // 3185162244
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::NewProp_InContainer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCSchemaRegistry, nullptr, "RegisterCatalog", Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::BVCSchemaRegistry_eventRegisterCatalog_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::BVCSchemaRegistry_eventRegisterCatalog_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCSchemaRegistry::execRegisterCatalog)
{
	P_GET_STRUCT_REF(FBVCMADescriptionContainer,Z_Param_Out_InContainer);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegisterCatalog(Z_Param_Out_InContainer);
	P_NATIVE_END;
}
// ********** End Class UBVCSchemaRegistry Function RegisterCatalog ********************************

// ********** Begin Class UBVCSchemaRegistry Function ResolveUObjectTypeName ***********************
struct Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics
{
	struct BVCSchemaRegistry_eventResolveUObjectTypeName_Parms
	{
		FString ModelClassName;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Schema" },
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelClassName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelClassName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::NewProp_ModelClassName = { "ModelClassName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaRegistry_eventResolveUObjectTypeName_Parms, ModelClassName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelClassName_MetaData), NewProp_ModelClassName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaRegistry_eventResolveUObjectTypeName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::NewProp_ModelClassName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCSchemaRegistry, nullptr, "ResolveUObjectTypeName", Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::BVCSchemaRegistry_eventResolveUObjectTypeName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::BVCSchemaRegistry_eventResolveUObjectTypeName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCSchemaRegistry::execResolveUObjectTypeName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ModelClassName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->ResolveUObjectTypeName(Z_Param_ModelClassName);
	P_NATIVE_END;
}
// ********** End Class UBVCSchemaRegistry Function ResolveUObjectTypeName *************************

// ********** Begin Class UBVCSchemaRegistry Function SetProjectPrefix *****************************
struct Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics
{
	struct BVCSchemaRegistry_eventSetProjectPrefix_Parms
	{
		FString InPrefix;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Schema" },
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InPrefix_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_InPrefix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::NewProp_InPrefix = { "InPrefix", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCSchemaRegistry_eventSetProjectPrefix_Parms, InPrefix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InPrefix_MetaData), NewProp_InPrefix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::NewProp_InPrefix,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCSchemaRegistry, nullptr, "SetProjectPrefix", Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::BVCSchemaRegistry_eventSetProjectPrefix_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::BVCSchemaRegistry_eventSetProjectPrefix_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCSchemaRegistry::execSetProjectPrefix)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_InPrefix);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetProjectPrefix(Z_Param_InPrefix);
	P_NATIVE_END;
}
// ********** End Class UBVCSchemaRegistry Function SetProjectPrefix *******************************

// ********** Begin Class UBVCSchemaRegistry *******************************************************
void UBVCSchemaRegistry::StaticRegisterNativesUBVCSchemaRegistry()
{
	UClass* Class = UBVCSchemaRegistry::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "FindByName", &UBVCSchemaRegistry::execFindByName },
		{ "RegisterCatalog", &UBVCSchemaRegistry::execRegisterCatalog },
		{ "ResolveUObjectTypeName", &UBVCSchemaRegistry::execResolveUObjectTypeName },
		{ "SetProjectPrefix", &UBVCSchemaRegistry::execSetProjectPrefix },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCSchemaRegistry;
UClass* UBVCSchemaRegistry::GetPrivateStaticClass()
{
	using TClass = UBVCSchemaRegistry;
	if (!Z_Registration_Info_UClass_UBVCSchemaRegistry.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCSchemaRegistry"),
			Z_Registration_Info_UClass_UBVCSchemaRegistry.InnerSingleton,
			StaticRegisterNativesUBVCSchemaRegistry,
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
	return Z_Registration_Info_UClass_UBVCSchemaRegistry.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCSchemaRegistry_NoRegister()
{
	return UBVCSchemaRegistry::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCSchemaRegistry_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "Schema/UBVCSchemaRegistry.h" },
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Catalog_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProjectPrefix_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/UBVCSchemaRegistry.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Catalog;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ProjectPrefix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCSchemaRegistry_FindByName, "FindByName" }, // 1343985432
		{ &Z_Construct_UFunction_UBVCSchemaRegistry_RegisterCatalog, "RegisterCatalog" }, // 418276385
		{ &Z_Construct_UFunction_UBVCSchemaRegistry_ResolveUObjectTypeName, "ResolveUObjectTypeName" }, // 2811204451
		{ &Z_Construct_UFunction_UBVCSchemaRegistry_SetProjectPrefix, "SetProjectPrefix" }, // 1466359428
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCSchemaRegistry>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBVCSchemaRegistry_Statics::NewProp_Catalog = { "Catalog", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCSchemaRegistry, Catalog), Z_Construct_UScriptStruct_FBVCMADescriptionContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Catalog_MetaData), NewProp_Catalog_MetaData) }; // 3185162244
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBVCSchemaRegistry_Statics::NewProp_ProjectPrefix = { "ProjectPrefix", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCSchemaRegistry, ProjectPrefix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProjectPrefix_MetaData), NewProp_ProjectPrefix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBVCSchemaRegistry_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCSchemaRegistry_Statics::NewProp_Catalog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCSchemaRegistry_Statics::NewProp_ProjectPrefix,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCSchemaRegistry_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBVCSchemaRegistry_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCSchemaRegistry_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCSchemaRegistry_Statics::ClassParams = {
	&UBVCSchemaRegistry::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBVCSchemaRegistry_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBVCSchemaRegistry_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCSchemaRegistry_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCSchemaRegistry_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCSchemaRegistry()
{
	if (!Z_Registration_Info_UClass_UBVCSchemaRegistry.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCSchemaRegistry.OuterSingleton, Z_Construct_UClass_UBVCSchemaRegistry_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCSchemaRegistry.OuterSingleton;
}
UBVCSchemaRegistry::UBVCSchemaRegistry(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCSchemaRegistry);
UBVCSchemaRegistry::~UBVCSchemaRegistry() {}
// ********** End Class UBVCSchemaRegistry *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCSchemaRegistry, UBVCSchemaRegistry::StaticClass, TEXT("UBVCSchemaRegistry"), &Z_Registration_Info_UClass_UBVCSchemaRegistry, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCSchemaRegistry), 1782368071U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h__Script_CatalystConnect_655656999(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
