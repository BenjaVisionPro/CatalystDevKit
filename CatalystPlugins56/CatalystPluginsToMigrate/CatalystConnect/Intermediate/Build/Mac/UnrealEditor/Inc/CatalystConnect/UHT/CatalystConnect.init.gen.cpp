// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCatalystConnect_init() {}
	CATALYSTCONNECT_API UFunction* Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_CatalystConnect;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_CatalystConnect()
	{
		if (!Z_Registration_Info_UPackage__Script_CatalystConnect.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/CatalystConnect",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x18F63519,
				0x462DC440,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_CatalystConnect.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_CatalystConnect.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_CatalystConnect(Z_Construct_UPackage__Script_CatalystConnect, TEXT("/Script/CatalystConnect"), Z_Registration_Info_UPackage__Script_CatalystConnect, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x18F63519, 0x462DC440));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
