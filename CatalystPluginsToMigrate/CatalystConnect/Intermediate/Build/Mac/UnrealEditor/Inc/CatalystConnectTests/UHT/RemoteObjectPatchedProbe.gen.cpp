// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Test/RemoteObjectPatchedProbe.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeRemoteObjectPatchedProbe() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECTTESTS_API UClass* Z_Construct_UClass_URemoteObjectPatchedProbe();
CATALYSTCONNECTTESTS_API UClass* Z_Construct_UClass_URemoteObjectPatchedProbe_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
UPackage* Z_Construct_UPackage__Script_CatalystConnectTests();
// ********** End Cross Module References **********************************************************

// ********** Begin Class URemoteObjectPatchedProbe Function OnPatched *****************************
struct Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics
{
	struct RemoteObjectPatchedProbe_eventOnPatched_Parms
	{
		FGuid Id;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// <-- needs a real name for UHT\n" },
#endif
		{ "ModuleRelativePath", "Public/Test/RemoteObjectPatchedProbe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "<-- needs a real name for UHT" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Id;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RemoteObjectPatchedProbe_eventOnPatched_Parms, Id), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Id_MetaData), NewProp_Id_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::NewProp_Id,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URemoteObjectPatchedProbe, nullptr, "OnPatched", Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::PropPointers), sizeof(Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::RemoteObjectPatchedProbe_eventOnPatched_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::Function_MetaDataParams), Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::RemoteObjectPatchedProbe_eventOnPatched_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URemoteObjectPatchedProbe::execOnPatched)
{
	P_GET_STRUCT_REF(FGuid,Z_Param_Out_Id);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPatched(Z_Param_Out_Id);
	P_NATIVE_END;
}
// ********** End Class URemoteObjectPatchedProbe Function OnPatched *******************************

// ********** Begin Class URemoteObjectPatchedProbe ************************************************
void URemoteObjectPatchedProbe::StaticRegisterNativesURemoteObjectPatchedProbe()
{
	UClass* Class = URemoteObjectPatchedProbe::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnPatched", &URemoteObjectPatchedProbe::execOnPatched },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_URemoteObjectPatchedProbe;
UClass* URemoteObjectPatchedProbe::GetPrivateStaticClass()
{
	using TClass = URemoteObjectPatchedProbe;
	if (!Z_Registration_Info_UClass_URemoteObjectPatchedProbe.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("RemoteObjectPatchedProbe"),
			Z_Registration_Info_UClass_URemoteObjectPatchedProbe.InnerSingleton,
			StaticRegisterNativesURemoteObjectPatchedProbe,
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
	return Z_Registration_Info_UClass_URemoteObjectPatchedProbe.InnerSingleton;
}
UClass* Z_Construct_UClass_URemoteObjectPatchedProbe_NoRegister()
{
	return URemoteObjectPatchedProbe::GetPrivateStaticClass();
}
struct Z_Construct_UClass_URemoteObjectPatchedProbe_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Test/RemoteObjectPatchedProbe.h" },
		{ "ModuleRelativePath", "Public/Test/RemoteObjectPatchedProbe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCalled_MetaData[] = {
		{ "ModuleRelativePath", "Public/Test/RemoteObjectPatchedProbe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bWasGameThread_MetaData[] = {
		{ "ModuleRelativePath", "Public/Test/RemoteObjectPatchedProbe.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bCalled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCalled;
	static void NewProp_bWasGameThread_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bWasGameThread;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URemoteObjectPatchedProbe_OnPatched, "OnPatched" }, // 1245951841
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URemoteObjectPatchedProbe>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bCalled_SetBit(void* Obj)
{
	((URemoteObjectPatchedProbe*)Obj)->bCalled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bCalled = { "bCalled", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URemoteObjectPatchedProbe), &Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bCalled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCalled_MetaData), NewProp_bCalled_MetaData) };
void Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bWasGameThread_SetBit(void* Obj)
{
	((URemoteObjectPatchedProbe*)Obj)->bWasGameThread = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bWasGameThread = { "bWasGameThread", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URemoteObjectPatchedProbe), &Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bWasGameThread_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bWasGameThread_MetaData), NewProp_bWasGameThread_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bCalled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::NewProp_bWasGameThread,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnectTests,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::ClassParams = {
	&URemoteObjectPatchedProbe::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::Class_MetaDataParams), Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URemoteObjectPatchedProbe()
{
	if (!Z_Registration_Info_UClass_URemoteObjectPatchedProbe.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URemoteObjectPatchedProbe.OuterSingleton, Z_Construct_UClass_URemoteObjectPatchedProbe_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URemoteObjectPatchedProbe.OuterSingleton;
}
URemoteObjectPatchedProbe::URemoteObjectPatchedProbe(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URemoteObjectPatchedProbe);
URemoteObjectPatchedProbe::~URemoteObjectPatchedProbe() {}
// ********** End Class URemoteObjectPatchedProbe **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h__Script_CatalystConnectTests_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URemoteObjectPatchedProbe, URemoteObjectPatchedProbe::StaticClass, TEXT("URemoteObjectPatchedProbe"), &Z_Registration_Info_UClass_URemoteObjectPatchedProbe, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URemoteObjectPatchedProbe), 490619909U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h__Script_CatalystConnectTests_803077659(TEXT("/Script/CatalystConnectTests"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h__Script_CatalystConnectTests_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h__Script_CatalystConnectTests_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
