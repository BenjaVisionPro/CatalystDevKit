// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Runtime/UBVCRemoteObject.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeUBVCRemoteObject() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObject();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObject_NoRegister();
CATALYSTCONNECT_API UFunction* Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FBVCPatched ***********************************************************
struct Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics
{
	struct _Script_CatalystConnect_eventBVCPatched_Parms
	{
		FGuid ObjectId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ObjectId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ObjectId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::NewProp_ObjectId = { "ObjectId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_CatalystConnect_eventBVCPatched_Parms, ObjectId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ObjectId_MetaData), NewProp_ObjectId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::NewProp_ObjectId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect, nullptr, "BVCPatched__DelegateSignature", Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::_Script_CatalystConnect_eventBVCPatched_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::_Script_CatalystConnect_eventBVCPatched_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FBVCPatched_DelegateWrapper(const FMulticastScriptDelegate& BVCPatched, FGuid const& ObjectId)
{
	struct _Script_CatalystConnect_eventBVCPatched_Parms
	{
		FGuid ObjectId;
	};
	_Script_CatalystConnect_eventBVCPatched_Parms Parms;
	Parms.ObjectId=ObjectId;
	BVCPatched.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FBVCPatched *************************************************************

// ********** Begin Class UBVCRemoteObject Function GetStringField *********************************
struct Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics
{
	struct BVCRemoteObject_eventGetStringField_Parms
	{
		FName Field;
		FString Out;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|RemoteObject" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_Field;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Out;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_Field = { "Field", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObject_eventGetStringField_Parms, Field), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_Out = { "Out", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObject_eventGetStringField_Parms, Out), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCRemoteObject_eventGetStringField_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCRemoteObject_eventGetStringField_Parms), &Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_Field,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_Out,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCRemoteObject, nullptr, "GetStringField", Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::BVCRemoteObject_eventGetStringField_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::BVCRemoteObject_eventGetStringField_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCRemoteObject_GetStringField()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCRemoteObject_GetStringField_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCRemoteObject::execGetStringField)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_Field);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetStringField(Z_Param_Field,Z_Param_Out_Out);
	P_NATIVE_END;
}
// ********** End Class UBVCRemoteObject Function GetStringField ***********************************

// ********** Begin Class UBVCRemoteObject Function SetStringField *********************************
struct Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics
{
	struct BVCRemoteObject_eventSetStringField_Parms
	{
		FName Field;
		FString In;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BVC|RemoteObject" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_In_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_Field;
	static const UECodeGen_Private::FStrPropertyParams NewProp_In;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_Field = { "Field", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObject_eventSetStringField_Parms, Field), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_In = { "In", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BVCRemoteObject_eventSetStringField_Parms, In), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_In_MetaData), NewProp_In_MetaData) };
void Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BVCRemoteObject_eventSetStringField_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BVCRemoteObject_eventSetStringField_Parms), &Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_Field,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_In,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBVCRemoteObject, nullptr, "SetStringField", Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::BVCRemoteObject_eventSetStringField_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::BVCRemoteObject_eventSetStringField_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBVCRemoteObject_SetStringField()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBVCRemoteObject_SetStringField_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBVCRemoteObject::execSetStringField)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_Field);
	P_GET_PROPERTY(FStrProperty,Z_Param_In);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SetStringField(Z_Param_Field,Z_Param_In);
	P_NATIVE_END;
}
// ********** End Class UBVCRemoteObject Function SetStringField ***********************************

// ********** Begin Class UBVCRemoteObject *********************************************************
void UBVCRemoteObject::StaticRegisterNativesUBVCRemoteObject()
{
	UClass* Class = UBVCRemoteObject::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetStringField", &UBVCRemoteObject::execGetStringField },
		{ "SetStringField", &UBVCRemoteObject::execSetStringField },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBVCRemoteObject;
UClass* UBVCRemoteObject::GetPrivateStaticClass()
{
	using TClass = UBVCRemoteObject;
	if (!Z_Registration_Info_UClass_UBVCRemoteObject.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BVCRemoteObject"),
			Z_Registration_Info_UClass_UBVCRemoteObject.InnerSingleton,
			StaticRegisterNativesUBVCRemoteObject,
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
	return Z_Registration_Info_UClass_UBVCRemoteObject.InnerSingleton;
}
UClass* Z_Construct_UClass_UBVCRemoteObject_NoRegister()
{
	return UBVCRemoteObject::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBVCRemoteObject_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "Runtime/UBVCRemoteObject.h" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[] = {
		{ "Category", "BVC|RemoteObject" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RemoteType_MetaData[] = {
		{ "Category", "BVC|RemoteObject" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnRemotePatched_MetaData[] = {
		{ "Category", "BVC|RemoteObject" },
		{ "ModuleRelativePath", "Public/Runtime/UBVCRemoteObject.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Id;
	static const UECodeGen_Private::FNamePropertyParams NewProp_RemoteType;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRemotePatched;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBVCRemoteObject_GetStringField, "GetStringField" }, // 3411436632
		{ &Z_Construct_UFunction_UBVCRemoteObject_SetStringField, "SetStringField" }, // 2717955240
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBVCRemoteObject>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBVCRemoteObject_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCRemoteObject, Id), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Id_MetaData), NewProp_Id_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UBVCRemoteObject_Statics::NewProp_RemoteType = { "RemoteType", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCRemoteObject, RemoteType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RemoteType_MetaData), NewProp_RemoteType_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBVCRemoteObject_Statics::NewProp_OnRemotePatched = { "OnRemotePatched", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBVCRemoteObject, OnRemotePatched), Z_Construct_UDelegateFunction_CatalystConnect_BVCPatched__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnRemotePatched_MetaData), NewProp_OnRemotePatched_MetaData) }; // 699706522
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBVCRemoteObject_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCRemoteObject_Statics::NewProp_Id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCRemoteObject_Statics::NewProp_RemoteType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBVCRemoteObject_Statics::NewProp_OnRemotePatched,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObject_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBVCRemoteObject_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObject_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBVCRemoteObject_Statics::ClassParams = {
	&UBVCRemoteObject::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBVCRemoteObject_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObject_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBVCRemoteObject_Statics::Class_MetaDataParams), Z_Construct_UClass_UBVCRemoteObject_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBVCRemoteObject()
{
	if (!Z_Registration_Info_UClass_UBVCRemoteObject.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBVCRemoteObject.OuterSingleton, Z_Construct_UClass_UBVCRemoteObject_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBVCRemoteObject.OuterSingleton;
}
UBVCRemoteObject::UBVCRemoteObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBVCRemoteObject);
UBVCRemoteObject::~UBVCRemoteObject() {}
// ********** End Class UBVCRemoteObject ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h__Script_CatalystConnect_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBVCRemoteObject, UBVCRemoteObject::StaticClass, TEXT("UBVCRemoteObject"), &Z_Registration_Info_UClass_UBVCRemoteObject, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBVCRemoteObject), 2576950807U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h__Script_CatalystConnect_4171605039(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h__Script_CatalystConnect_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
