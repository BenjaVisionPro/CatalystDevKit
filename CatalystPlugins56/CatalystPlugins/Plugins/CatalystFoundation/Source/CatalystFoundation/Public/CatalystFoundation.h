/**
 * @file CatalystFoundation.h
 * @brief CatalystFoundation provides core base classes and utilities that formalize shared patterns used across all Catalyst plugins.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once
#include "Modules/ModuleManager.h"

CATALYSTFOUNDATION_API DECLARE_LOG_CATEGORY_EXTERN(LogCF, Log, All);

class FCatalystFoundationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};