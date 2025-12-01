/**
 * @file CatalystFoundation.cpp
 * @brief Implementation for CatalystFoundation.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#include "CatalystFoundation.h"
#include "Log/CFLog.h"

DEFINE_LOG_CATEGORY(LogCF);

#define LOCTEXT_NAMESPACE "FCatalystFoundationModule"

void FCatalystFoundationModule::StartupModule()
{
    CF_INFO(TEXT("Catalyst Foundation module started."));
}

void FCatalystFoundationModule::ShutdownModule()
{
    CF_INFO(TEXT("Catalyst Foundation module shut down."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCatalystFoundationModule, CatalystFoundation)