// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Codegen/UBVCStubGenerator.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCStubGenerator() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCStubGenerator();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCStubGenerator_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBVCStubGenerator Function GenerateStubs *********************************
struct Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Codegen" },
		{ "ModuleRelativePath", "Public/Codegen/UBVCStubGenerator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCStubGenerator, nullptr, "GenerateStubs", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCStubGenerator::execGenerateStubs)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->GenerateStubs();
	P_NATIVE_END;
}
// ********** End Class UBVCStubGenerator Function GenerateStubs ***********************************

// ********** Begin Class UBVCStubGenerator ********************************************************
void UBVCStubGenerator::StaticRegisterNativesUBVCStubGenerator()
{
	UClass* Class = UBVCStubGenerator::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GenerateStubs", &UBVCStubGenerator::execGenerateStubs },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCStubGenerator;
UClass* UBVCStubGenerator::GetPrivateStaticClass()
{
	using TClass = UBVCStubGenerator;
	if (!Z_Registration_Info_UClass_UBVCStubGenerator.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCStubGenerator"),
			Z_Registration_Info_UClass_UBVCStubGenerator.InnerSingleton,
			StaticRegisterNativesUBVCStubGenerator,
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
	return Z_Registration_Info_UClass_UBVCStubGenerator.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCStubGenerator_NoRegister()
{
	return UBVCStubGenerator::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCStubGenerator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Codegen/UBVCStubGenerator.h" },
		{ "ModuleRelativePath", "Public/Codegen/UBVCStubGenerator.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCStubGenerator_GenerateStubs, "GenerateStubs" }, // 3006283847
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCStubGenerator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBVCStubGenerator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCStubGenerator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCStubGenerator_Statics::ClassParams = {
	&UBVCStubGenerator::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCStubGenerator_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCStubGenerator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCStubGenerator()
{
	if (!Z_Registration_Info_UClass_UBVCStubGenerator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCStubGenerator.OuterSingleton, Z_Construct_UClass_UBVCStubGenerator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCStubGenerator.OuterSingleton;
}
UBVCStubGenerator::UBVCStubGenerator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCStubGenerator);
UBVCStubGenerator::~UBVCStubGenerator() {}
// ********** End Class UBVCStubGenerator **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCStubGenerator_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCStubGenerator, UBVCStubGenerator::StaticClass, TEXT("UBVCStubGenerator"), &Z_Registration_Info_UClass_UBVCStubGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCStubGenerator), 3881562298U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCStubGenerator_h__Script_CatalystConnect_3989553373(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCStubGenerator_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Codegen_UBVCStubGenerator_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
