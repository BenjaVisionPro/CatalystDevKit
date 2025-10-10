// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Connection/UBVCConnection.h"
#include "Connection/BVCConnectionConfig.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCConnection() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnection();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnection_NoRegister();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnectionManager_NoRegister();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FBVCConnectionConfig();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBVCConnection Function Connect ******************************************
struct Z_Construct_UFunction_UBVCConnection_Connect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Connect / Disconnect / IsConnected proxy to ConnectionManager. */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Connect / Disconnect / IsConnected proxy to ConnectionManager." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnection_Connect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnection, nullptr, "Connect", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_Connect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnection_Connect_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBVCConnection_Connect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnection_Connect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnection::execConnect)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Connect();
	P_NATIVE_END;
}
// ********** End Class UBVCConnection Function Connect ********************************************

// ********** Begin Class UBVCConnection Function Disconnect ***************************************
struct Z_Construct_UFunction_UBVCConnection_Disconnect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnection_Disconnect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnection, nullptr, "Disconnect", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_Disconnect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnection_Disconnect_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBVCConnection_Disconnect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnection_Disconnect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnection::execDisconnect)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Disconnect();
	P_NATIVE_END;
}
// ********** End Class UBVCConnection Function Disconnect *****************************************

// ********** Begin Class UBVCConnection Function InitializeConnection *****************************
struct Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics
{
	struct BVCConnection_eventInitializeConnection_Parms
	{
		FBVCConnectionConfig InConfig;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Build the pipeline with the given config (does not Connect). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Build the pipeline with the given config (does not Connect)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InConfig_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InConfig;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::NewProp_InConfig = { "InConfig", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnection_eventInitializeConnection_Parms, InConfig), Z_Construct_UScriptStruct_FBVCConnectionConfig, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InConfig_MetaData), NewProp_InConfig_MetaData) }; // 3760486832
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::NewProp_InConfig,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnection, nullptr, "InitializeConnection", Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::BVCConnection_eventInitializeConnection_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::BVCConnection_eventInitializeConnection_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnection_InitializeConnection()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnection_InitializeConnection_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnection::execInitializeConnection)
{
	P_GET_STRUCT_REF(FBVCConnectionConfig,Z_Param_Out_InConfig);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeConnection(Z_Param_Out_InConfig);
	P_NATIVE_END;
}
// ********** End Class UBVCConnection Function InitializeConnection *******************************

// ********** Begin Class UBVCConnection Function IsConnected **************************************
struct Z_Construct_UFunction_UBVCConnection_IsConnected_Statics
{
	struct BVCConnection_eventIsConnected_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCConnection_eventIsConnected_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCConnection_eventIsConnected_Parms), &Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnection, nullptr, "IsConnected", Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::BVCConnection_eventIsConnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::BVCConnection_eventIsConnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnection_IsConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnection_IsConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnection::execIsConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsConnected();
	P_NATIVE_END;
}
// ********** End Class UBVCConnection Function IsConnected ****************************************

// ********** Begin Class UBVCConnection Function Send *********************************************
struct Z_Construct_UFunction_UBVCConnection_Send_Statics
{
	struct BVCConnection_eventSend_Parms
	{
		int32 ChannelId;
		uint8 Priority;
		TArray<uint8> Bytes;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Send a message (bytes already encoded as an envelope + message). */" },
#endif
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Send a message (bytes already encoded as an envelope + message)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bytes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChannelId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Priority;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Bytes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Bytes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_ChannelId = { "ChannelId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnection_eventSend_Parms, ChannelId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_Priority = { "Priority", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnection_eventSend_Parms, Priority), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_Bytes_Inner = { "Bytes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_Bytes = { "Bytes", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCConnection_eventSend_Parms, Bytes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bytes_MetaData), NewProp_Bytes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCConnection_Send_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_ChannelId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_Priority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_Bytes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCConnection_Send_Statics::NewProp_Bytes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_Send_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCConnection_Send_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCConnection, nullptr, "Send", Z_Construct_UFunction_UBVCConnection_Send_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_Send_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCConnection_Send_Statics::BVCConnection_eventSend_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCConnection_Send_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCConnection_Send_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCConnection_Send_Statics::BVCConnection_eventSend_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCConnection_Send()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCConnection_Send_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCConnection::execSend)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ChannelId);
	P_GET_PROPERTY(FByteProperty,Z_Param_Priority);
	P_GET_TARRAY_REF(uint8,Z_Param_Out_Bytes);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Send(Z_Param_ChannelId,Z_Param_Priority,Z_Param_Out_Bytes);
	P_NATIVE_END;
}
// ********** End Class UBVCConnection Function Send ***********************************************

// ********** Begin Class UBVCConnection ***********************************************************
void UBVCConnection::StaticRegisterNativesUBVCConnection()
{
	UClass* Class = UBVCConnection::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Connect", &UBVCConnection::execConnect },
		{ "Disconnect", &UBVCConnection::execDisconnect },
		{ "InitializeConnection", &UBVCConnection::execInitializeConnection },
		{ "IsConnected", &UBVCConnection::execIsConnected },
		{ "Send", &UBVCConnection::execSend },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCConnection;
UClass* UBVCConnection::GetPrivateStaticClass()
{
	using TClass = UBVCConnection;
	if (!Z_Registration_Info_UClass_UBVCConnection.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCConnection"),
			Z_Registration_Info_UClass_UBVCConnection.InnerSingleton,
			StaticRegisterNativesUBVCConnection,
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
	return Z_Registration_Info_UClass_UBVCConnection.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCConnection_NoRegister()
{
	return UBVCConnection::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCConnection_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * UBVCConnection\n * Owns the per-connection pipeline:\n *   TransportWorker -> EnvelopeReader -> MessageReader -> MessageRouter\n * Surfaces router delegates for higher layers.\n */" },
#endif
		{ "IncludePath", "Connection/UBVCConnection.h" },
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UBVCConnection\nOwns the per-connection pipeline:\n  TransportWorker -> EnvelopeReader -> MessageReader -> MessageRouter\nSurfaces router delegates for higher layers." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConnectionManager_MetaData[] = {
		{ "ModuleRelativePath", "Public/Connection/UBVCConnection.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ConnectionManager;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCConnection_Connect, "Connect" }, // 197050483
		{ &Z_Construct_UFunction_UBVCConnection_Disconnect, "Disconnect" }, // 2361838775
		{ &Z_Construct_UFunction_UBVCConnection_InitializeConnection, "InitializeConnection" }, // 1421153577
		{ &Z_Construct_UFunction_UBVCConnection_IsConnected, "IsConnected" }, // 2492875661
		{ &Z_Construct_UFunction_UBVCConnection_Send, "Send" }, // 4172956466
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCConnection>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBVCConnection_Statics::NewProp_ConnectionManager = { "ConnectionManager", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCConnection, ConnectionManager), Z_Construct_UClass_UBVCConnectionManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConnectionManager_MetaData), NewProp_ConnectionManager_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBVCConnection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCConnection_Statics::NewProp_ConnectionManager,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCConnection_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBVCConnection_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCConnection_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCConnection_Statics::ClassParams = {
	&UBVCConnection::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBVCConnection_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBVCConnection_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCConnection_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCConnection_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCConnection()
{
	if (!Z_Registration_Info_UClass_UBVCConnection.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCConnection.OuterSingleton, Z_Construct_UClass_UBVCConnection_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCConnection.OuterSingleton;
}
UBVCConnection::UBVCConnection(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCConnection);
UBVCConnection::~UBVCConnection() {}
// ********** End Class UBVCConnection *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCConnection, UBVCConnection::StaticClass, TEXT("UBVCConnection"), &Z_Registration_Info_UClass_UBVCConnection, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCConnection), 838401687U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h__Script_CatalystConnect_130558788(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
