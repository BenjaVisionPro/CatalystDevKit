// CFEditorModule.cpp

#include "CFEditorModule.h"

DEFINE_LOG_CATEGORY(LogCFEditor);

// 🔁 Replace with your actual tab name if you expose a Nomad tab:
static const FName CatalystFoundationEditorTabName("Catalyst:Foundation");

#define LOCTEXT_NAMESPACE "FCFEditorModule"

void FCFEditorModule::StartupModule()
{
}

void FCFEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCFEditorModule, CatalystFoundationEditor)
