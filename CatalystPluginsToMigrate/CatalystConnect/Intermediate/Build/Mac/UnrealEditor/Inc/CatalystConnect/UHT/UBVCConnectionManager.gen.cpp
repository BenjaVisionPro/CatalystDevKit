// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Connection/UBVCConnectionManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCConnectionManager() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnectionManager();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnectionManager_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCFlowRates();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBVCFlowRates *****************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBVCFlowRates;
class UScriptStruct* FBVCFlowRates::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCFlowRates.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBVCFlowRates.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBVCFlowRates, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("BVCFlowRates"));
	}
	return Z_Registration_Info_UScriptStruct_FBVCFlowRates.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBVCFlowRates_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Simple flow configuration for this connection (0 == unlimited). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple flow configuration for this connection (0 == unlimited)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxOutboundBytesPerSecond_MetaData[] = {
		{ "Category", "BVC|Flow" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max outbound throughput in bytes per second (0 = unlimited). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max outbound throughput in bytes per second (0 = unlimited)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxInboundBytesPerSecond_MetaData[] = {
		{ "Category", "BVC|Flow" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max inbound throughput in bytes per second (0 = unlimited). Reserved. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max inbound throughput in bytes per second (0 = unlimited). Reserved." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FInt64PropertyParams NewProp_MaxOutboundBytesPerSecond;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_MaxInboundBytesPerSecond;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBVCFlowRates>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FBVCFlowRates_Statics::NewProp_MaxOutboundBytesPerSecond = { "MaxOutboundBytesPerSecond", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCFlowRates, MaxOutboundBytesPerSecond), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxOutboundBytesPerSecond_MetaData), NewProp_MaxOutboundBytesPerSecond_MetaData) };
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FBVCFlowRates_Statics::NewProp_MaxInboundBytesPerSecond = { "MaxInboundBytesPerSecond", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBVCFlowRates, MaxInboundBytesPerSecond), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxInboundBytesPerSecond_MetaData), NewProp_MaxInboundBytesPerSecond_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBVCFlowRates_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCFlowRates_Statics::NewProp_MaxOutboundBytesPerSecond,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBVCFlowRates_Statics::NewProp_MaxInboundBytesPerSecond,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCFlowRates_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBVCFlowRates_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"BVCFlowRates",
	Z_Construct_UScriptStruct_FBVCFlowRates_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCFlowRates_Statics::PropPointers),
	sizeof(FBVCFlowRates),
	alignof(FBVCFlowRates),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBVCFlowRates_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBVCFlowRates_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBVCFlowRates()
{
	if (!Z_Registration_Info_UScriptStruct_FBVCFlowRates.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBVCFlowRates.InnerSingleton, Z_Construct_UScriptStruct_FBVCFlowRates_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBVCFlowRates.InnerSingleton;
}
// ********** End ScriptStruct FBVCFlowRates *******************************************************

// ********** Begin Class UBVCConnectionManager Function Connect ***********************************
struct Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics
{
	struct BVCConnectionManager_eventConnect_Parms
	{
		FString Url;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Connect using the given URL (loopback://, ws://, wss://, tcp://, http://, https://). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Connect using the given URL (loopback://, ws://, wss://, tcp://, http://, https://)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Url_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Url;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::NewProp_Url = { "Url", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnectionManager_eventConnect_Parms, Url), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Url_MetaData), NewProp_Url_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::NewProp_Url,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnectionManager, nullptr, "Connect", Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::BVCConnectionManager_eventConnect_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::BVCConnectionManager_eventConnect_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnectionManager_Connect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnectionManager_Connect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnectionManager::execConnect)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Url);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Connect(Z_Param_Url);
	P_NATIVE_END;
}
// ********** End Class UBVCConnectionManager Function Connect *************************************

// ********** Begin Class UBVCConnectionManager Function Disconnect ********************************
struct Z_Construct_UFunction_UBVCConnectionManager_Disconnect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Disconnect and tear down transport. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Disconnect and tear down transport." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnectionManager_Disconnect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnectionManager, nullptr, "Disconnect", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_Disconnect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnectionManager_Disconnect_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBVCConnectionManager_Disconnect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnectionManager_Disconnect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnectionManager::execDisconnect)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Disconnect();
	P_NATIVE_END;
}
// ********** End Class UBVCConnectionManager Function Disconnect **********************************

// ********** Begin Class UBVCConnectionManager Function GetFlowRates ******************************
struct Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics
{
	struct BVCConnectionManager_eventGetFlowRates_Parms
	{
		FBVCFlowRates ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Flow" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current flow caps. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current flow caps." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnectionManager_eventGetFlowRates_Parms, ReturnValue), Z_Construct_UScriptStruct_FBVCFlowRates, METADATA_PARAMS(0, nullptr) }; // 483091603
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnectionManager, nullptr, "GetFlowRates", Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::BVCConnectionManager_eventGetFlowRates_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::BVCConnectionManager_eventGetFlowRates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnectionManager::execGetFlowRates)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBVCFlowRates*)Z_Param__Result=P_THIS->GetFlowRates();
	P_NATIVE_END;
}
// ********** End Class UBVCConnectionManager Function GetFlowRates ********************************

// ********** Begin Class UBVCConnectionManager Function IsConnected *******************************
struct Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics
{
	struct BVCConnectionManager_eventIsConnected_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCConnectionManager_eventIsConnected_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCConnectionManager_eventIsConnected_Parms), &Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnectionManager, nullptr, "IsConnected", Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::BVCConnectionManager_eventIsConnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::BVCConnectionManager_eventIsConnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnectionManager_IsConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnectionManager_IsConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnectionManager::execIsConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsConnected();
	P_NATIVE_END;
}
// ********** End Class UBVCConnectionManager Function IsConnected *********************************

// ********** Begin Class UBVCConnectionManager Function SetFlowRates ******************************
struct Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics
{
	struct BVCConnectionManager_eventSetFlowRates_Parms
	{
		FBVCFlowRates Rates;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Flow" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Update flow caps at runtime (0 == unlimited). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Update flow caps at runtime (0 == unlimited)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rates_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Rates;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::NewProp_Rates = { "Rates", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnectionManager_eventSetFlowRates_Parms, Rates), Z_Construct_UScriptStruct_FBVCFlowRates, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rates_MetaData), NewProp_Rates_MetaData) }; // 483091603
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::NewProp_Rates,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnectionManager, nullptr, "SetFlowRates", Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::BVCConnectionManager_eventSetFlowRates_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::BVCConnectionManager_eventSetFlowRates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnectionManager::execSetFlowRates)
{
	P_GET_STRUCT_REF(FBVCFlowRates,Z_Param_Out_Rates);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetFlowRates(Z_Param_Out_Rates);
	P_NATIVE_END;
}
// ********** End Class UBVCConnectionManager Function SetFlowRates ********************************

// ********** Begin Class UBVCConnectionManager ****************************************************
void UBVCConnectionManager::StaticRegisterNativesUBVCConnectionManager()
{
	UClass* Class = UBVCConnectionManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Connect", &UBVCConnectionManager::execConnect },
		{ "Disconnect", &UBVCConnectionManager::execDisconnect },
		{ "GetFlowRates", &UBVCConnectionManager::execGetFlowRates },
		{ "IsConnected", &UBVCConnectionManager::execIsConnected },
		{ "SetFlowRates", &UBVCConnectionManager::execSetFlowRates },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCConnectionManager;
UClass* UBVCConnectionManager::GetPrivateStaticClass()
{
	using TClass = UBVCConnectionManager;
	if (!Z_Registration_Info_UClass_UBVCConnectionManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCConnectionManager"),
			Z_Registration_Info_UClass_UBVCConnectionManager.InnerSingleton,
			StaticRegisterNativesUBVCConnectionManager,
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
	return Z_Registration_Info_UClass_UBVCConnectionManager.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCConnectionManager_NoRegister()
{
	return UBVCConnectionManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCConnectionManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * ConnectionManager\n * - Owns a single IBVCTransportInterface instance created from a URL\n * - Exposes OnInboundFrame() for workers to subscribe to\n * - Forwards SendBytes()/Connect()/Disconnect()\n * - Owns optional FlowControl (token bucket) for pacing\n */" },
#endif
		{ "IncludePath", "Connection/UBVCConnectionManager.h" },
		{ "ModuleRelativePath", "Public/Connection/UBVCConnectionManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ConnectionManager\n- Owns a single IBVCTransportInterface instance created from a URL\n- Exposes OnInboundFrame() for workers to subscribe to\n- Forwards SendBytes()/Connect()/Disconnect()\n- Owns optional FlowControl (token bucket) for pacing" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCConnectionManager_Connect, "Connect" }, // 14292547
		{ &Z_Construct_UFunction_UBVCConnectionManager_Disconnect, "Disconnect" }, // 359763342
		{ &Z_Construct_UFunction_UBVCConnectionManager_GetFlowRates, "GetFlowRates" }, // 1759351535
		{ &Z_Construct_UFunction_UBVCConnectionManager_IsConnected, "IsConnected" }, // 2060424294
		{ &Z_Construct_UFunction_UBVCConnectionManager_SetFlowRates, "SetFlowRates" }, // 2459972611
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCConnectionManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBVCConnectionManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCConnectionManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCConnectionManager_Statics::ClassParams = {
	&UBVCConnectionManager::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCConnectionManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCConnectionManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCConnectionManager()
{
	if (!Z_Registration_Info_UClass_UBVCConnectionManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCConnectionManager.OuterSingleton, Z_Construct_UClass_UBVCConnectionManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCConnectionManager.OuterSingleton;
}
UBVCConnectionManager::UBVCConnectionManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCConnectionManager);
UBVCConnectionManager::~UBVCConnectionManager() {}
// ********** End Class UBVCConnectionManager ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h__Script_CatalystConnect_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBVCFlowRates::StaticStruct, Z_Construct_UScriptStruct_FBVCFlowRates_Statics::NewStructOps, TEXT("BVCFlowRates"), &Z_Registration_Info_UScriptStruct_FBVCFlowRates, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBVCFlowRates), 483091603U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCConnectionManager, UBVCConnectionManager::StaticClass, TEXT("UBVCConnectionManager"), &Z_Registration_Info_UClass_UBVCConnectionManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCConnectionManager), 2521588727U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h__Script_CatalystConnect_58042713(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h__Script_CatalystConnect_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
