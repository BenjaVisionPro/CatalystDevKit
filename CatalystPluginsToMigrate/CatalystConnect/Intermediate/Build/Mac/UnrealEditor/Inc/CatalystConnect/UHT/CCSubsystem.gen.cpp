// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SubSystem/CCSubsystem.h"
#include "Connection/BVCConnectionConfig.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCCSubsystem() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnection_NoRegister();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSubsystem();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSubsystem_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCConnectionConfig();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCCSubsystem Function CreateConnection ***********************************
struct Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics
{
	struct CCSubsystem_eventCreateConnection_Parms
	{
		FBVCConnectionConfig Config;
		UBVCConnection* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Create a new connection UObject, initialize it, and return it. Caller owns the reference. */" },
#endif
		{ "ModuleRelativePath", "Public/SubSystem/CCSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a new connection UObject, initialize it, and return it. Caller owns the reference." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Config_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Config;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::NewProp_Config = { "Config", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CCSubsystem_eventCreateConnection_Parms, Config), Z_Construct_UScriptStruct_FBVCConnectionConfig, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Config_MetaData), NewProp_Config_MetaData) }; // 3760486832
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CCSubsystem_eventCreateConnection_Parms, ReturnValue), Z_Construct_UClass_UBVCConnection_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::NewProp_Config,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCCSubsystem, nullptr, "CreateConnection", Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::CCSubsystem_eventCreateConnection_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::CCSubsystem_eventCreateConnection_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCCSubsystem_CreateConnection()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCCSubsystem_CreateConnection_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCCSubsystem::execCreateConnection)
{
	P_GET_STRUCT_REF(FBVCConnectionConfig,Z_Param_Out_Config);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UBVCConnection**)Z_Param__Result=P_THIS->CreateConnection(Z_Param_Out_Config);
	P_NATIVE_END;
}
// ********** End Class UCCSubsystem Function CreateConnection *************************************

// ********** Begin Class UCCSubsystem Function Get ************************************************
struct Z_Construct_UFunction_UCCSubsystem_Get_Statics
{
	struct CCSubsystem_eventGet_Parms
	{
		const UObject* WorldContextObject;
		UCCSubsystem* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Convenience accessor from any world context. */" },
#endif
		{ "ModuleRelativePath", "Public/SubSystem/CCSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convenience accessor from any world context." },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCCSubsystem_Get_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CCSubsystem_eventGet_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCCSubsystem_Get_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CCSubsystem_eventGet_Parms, ReturnValue), Z_Construct_UClass_UCCSubsystem_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCCSubsystem_Get_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCCSubsystem_Get_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCCSubsystem_Get_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCCSubsystem_Get_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCCSubsystem_Get_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCCSubsystem, nullptr, "Get", Z_Construct_UFunction_UCCSubsystem_Get_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCCSubsystem_Get_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCCSubsystem_Get_Statics::CCSubsystem_eventGet_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCCSubsystem_Get_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCCSubsystem_Get_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCCSubsystem_Get_Statics::CCSubsystem_eventGet_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCCSubsystem_Get()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCCSubsystem_Get_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCCSubsystem::execGet)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UCCSubsystem**)Z_Param__Result=UCCSubsystem::Get(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// ********** End Class UCCSubsystem Function Get **************************************************

// ********** Begin Class UCCSubsystem *************************************************************
void UCCSubsystem::StaticRegisterNativesUCCSubsystem()
{
	UClass* Class = UCCSubsystem::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "CreateConnection", &UCCSubsystem::execCreateConnection },
		{ "Get", &UCCSubsystem::execGet },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCCSubsystem;
UClass* UCCSubsystem::GetPrivateStaticClass()
{
	using TClass = UCCSubsystem;
	if (!Z_Registration_Info_UClass_UCCSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CCSubsystem"),
			Z_Registration_Info_UClass_UCCSubsystem.InnerSingleton,
			StaticRegisterNativesUCCSubsystem,
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
	return Z_Registration_Info_UClass_UCCSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UCCSubsystem_NoRegister()
{
	return UCCSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCCSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * UCCSubsystem\n *\n * Thin factory/locator for BVC connections.\n * - Does NOT store or track created connections.\n * - Callers own the returned UBVCConnection objects.\n */" },
#endif
		{ "IncludePath", "SubSystem/CCSubsystem.h" },
		{ "ModuleRelativePath", "Public/SubSystem/CCSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UCCSubsystem\n\nThin factory/locator for BVC connections.\n- Does NOT store or track created connections.\n- Callers own the returned UBVCConnection objects." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCCSubsystem_CreateConnection, "CreateConnection" }, // 4141307133
		{ &Z_Construct_UFunction_UCCSubsystem_Get, "Get" }, // 3860167213
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCCSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCCSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCCSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCCSubsystem_Statics::ClassParams = {
	&UCCSubsystem::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCCSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UCCSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCCSubsystem()
{
	if (!Z_Registration_Info_UClass_UCCSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCCSubsystem.OuterSingleton, Z_Construct_UClass_UCCSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCCSubsystem.OuterSingleton;
}
UCCSubsystem::UCCSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCCSubsystem);
UCCSubsystem::~UCCSubsystem() {}
// ********** End Class UCCSubsystem ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCCSubsystem, UCCSubsystem::StaticClass, TEXT("UCCSubsystem"), &Z_Registration_Info_UClass_UCCSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCCSubsystem), 4034104554U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h__Script_CatalystConnect_604112963(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
