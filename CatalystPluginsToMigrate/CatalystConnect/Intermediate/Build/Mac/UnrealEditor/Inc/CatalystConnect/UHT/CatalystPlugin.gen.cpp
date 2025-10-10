// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/CatalystPlugin.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCatalystPlugin() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCatalystPlugin();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCatalystPlugin_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCatalystPlugin Function MyCustomFunction ********************************
struct Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Example function\n" },
#endif
		{ "ModuleRelativePath", "Private/Core/CatalystPlugin.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Example function" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCatalystPlugin, nullptr, "MyCustomFunction", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCatalystPlugin::execMyCustomFunction)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MyCustomFunction();
	P_NATIVE_END;
}
// ********** End Class UCatalystPlugin Function MyCustomFunction **********************************

// ********** Begin Class UCatalystPlugin **********************************************************
void UCatalystPlugin::StaticRegisterNativesUCatalystPlugin()
{
	UClass* Class = UCatalystPlugin::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "MyCustomFunction", &UCatalystPlugin::execMyCustomFunction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCatalystPlugin;
UClass* UCatalystPlugin::GetPrivateStaticClass()
{
	using TClass = UCatalystPlugin;
	if (!Z_Registration_Info_UClass_UCatalystPlugin.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CatalystPlugin"),
			Z_Registration_Info_UClass_UCatalystPlugin.InnerSingleton,
			StaticRegisterNativesUCatalystPlugin,
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
	return Z_Registration_Info_UClass_UCatalystPlugin.InnerSingleton;
}
UClass* Z_Construct_UClass_UCatalystPlugin_NoRegister()
{
	return UCatalystPlugin::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCatalystPlugin_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "Core/CatalystPlugin.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Private/Core/CatalystPlugin.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MyCustomProperty_MetaData[] = {
		{ "Category", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Example property\n" },
#endif
		{ "ModuleRelativePath", "Private/Core/CatalystPlugin.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Example property" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_MyCustomProperty;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCatalystPlugin_MyCustomFunction, "MyCustomFunction" }, // 3576712193
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCatalystPlugin>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCatalystPlugin_Statics::NewProp_MyCustomProperty = { "MyCustomProperty", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCatalystPlugin, MyCustomProperty), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MyCustomProperty_MetaData), NewProp_MyCustomProperty_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCatalystPlugin_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCatalystPlugin_Statics::NewProp_MyCustomProperty,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCatalystPlugin_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCatalystPlugin_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCatalystPlugin_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCatalystPlugin_Statics::ClassParams = {
	&UCatalystPlugin::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UCatalystPlugin_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UCatalystPlugin_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCatalystPlugin_Statics::Class_MetaDataParams), Z_Construct_UClass_UCatalystPlugin_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCatalystPlugin()
{
	if (!Z_Registration_Info_UClass_UCatalystPlugin.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCatalystPlugin.OuterSingleton, Z_Construct_UClass_UCatalystPlugin_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCatalystPlugin.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCatalystPlugin);
UCatalystPlugin::~UCatalystPlugin() {}
// ********** End Class UCatalystPlugin ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Private_Core_CatalystPlugin_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCatalystPlugin, UCatalystPlugin::StaticClass, TEXT("UCatalystPlugin"), &Z_Registration_Info_UClass_UCatalystPlugin, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCatalystPlugin), 2432969753U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Private_Core_CatalystPlugin_h__Script_CatalystConnect_1169512333(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Private_Core_CatalystPlugin_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Private_Core_CatalystPlugin_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
