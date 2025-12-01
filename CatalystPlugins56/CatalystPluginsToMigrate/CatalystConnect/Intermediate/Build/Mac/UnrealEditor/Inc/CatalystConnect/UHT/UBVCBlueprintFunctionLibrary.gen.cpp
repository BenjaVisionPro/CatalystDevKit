// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Codegen/UBVCBlueprintFunctionLibrary.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCBlueprintFunctionLibrary() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCBlueprintFunctionLibrary();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCBlueprintFunctionLibrary_NoRegister();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBVCBlueprintFunctionLibrary Function GetStringField *********************
struct Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics
{
	struct BVCBlueprintFunctionLibrary_eventGetStringField_Parms
	{
		UBVCRemoteObject* Obj;
		FName Field;
		FString Out;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|RemoteObject" },
		{ "ModuleRelativePath", "Public/Codegen/UBVCBlueprintFunctionLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Obj;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Field;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Out;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_Obj = { "Obj", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCBlueprintFunctionLibrary_eventGetStringField_Parms, Obj), Z_Construct_UClass_UBVCRemoteObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_Field = { "Field", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCBlueprintFunctionLibrary_eventGetStringField_Parms, Field), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_Out = { "Out", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCBlueprintFunctionLibrary_eventGetStringField_Parms, Out), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCBlueprintFunctionLibrary_eventGetStringField_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCBlueprintFunctionLibrary_eventGetStringField_Parms), &Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_Obj,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_Field,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_Out,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCBlueprintFunctionLibrary, nullptr, "GetStringField", Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::BVCBlueprintFunctionLibrary_eventGetStringField_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::BVCBlueprintFunctionLibrary_eventGetStringField_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCBlueprintFunctionLibrary::execGetStringField)
{
	P_GET_OBJECT(UBVCRemoteObject,Z_Param_Obj);
	P_GET_PROPERTY(FNameProperty,Z_Param_Field);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UBVCBlueprintFunctionLibrary::GetStringField(Z_Param_Obj,Z_Param_Field,Z_Param_Out_Out);
	P_NATIVE_END;
}
// ********** End Class UBVCBlueprintFunctionLibrary Function GetStringField ***********************

// ********** Begin Class UBVCBlueprintFunctionLibrary *********************************************
void UBVCBlueprintFunctionLibrary::StaticRegisterNativesUBVCBlueprintFunctionLibrary()
{
	UClass* Class = UBVCBlueprintFunctionLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetStringField", &UBVCBlueprintFunctionLibrary::execGetStringField },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary;
UClass* UBVCBlueprintFunctionLibrary::GetPrivateStaticClass()
{
	using TClass = UBVCBlueprintFunctionLibrary;
	if (!Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCBlueprintFunctionLibrary"),
			Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary.InnerSingleton,
			StaticRegisterNativesUBVCBlueprintFunctionLibrary,
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
	return Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCBlueprintFunctionLibrary_NoRegister()
{
	return UBVCBlueprintFunctionLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Codegen/UBVCBlueprintFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/Codegen/UBVCBlueprintFunctionLibrary.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCBlueprintFunctionLibrary_GetStringField, "GetStringField" }, // 3506973118
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCBlueprintFunctionLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics::ClassParams = {
	&UBVCBlueprintFunctionLibrary::StaticClass,
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
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCBlueprintFunctionLibrary()
{
	if (!Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary.OuterSingleton, Z_Construct_UClass_UBVCBlueprintFunctionLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary.OuterSingleton;
}
UBVCBlueprintFunctionLibrary::UBVCBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCBlueprintFunctionLibrary);
UBVCBlueprintFunctionLibrary::~UBVCBlueprintFunctionLibrary() {}
// ********** End Class UBVCBlueprintFunctionLibrary ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCBlueprintFunctionLibrary_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCBlueprintFunctionLibrary, UBVCBlueprintFunctionLibrary::StaticClass, TEXT("UBVCBlueprintFunctionLibrary"), &Z_Registration_Info_UClass_UBVCBlueprintFunctionLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCBlueprintFunctionLibrary), 1084318801U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCBlueprintFunctionLibrary_h__Script_CatalystConnect_1107486886(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCBlueprintFunctionLibrary_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCBlueprintFunctionLibrary_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
