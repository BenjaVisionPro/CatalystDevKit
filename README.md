# Catalyst DevKit

Catalyst DevKit gives developers a local, inspectable environment for building
Catalyst applications and multiplayer game backends in Smalltalk. You can work
with live objects, run services, explore process models, and debug behaviour in
GT before committing to a deployment. The platform is evolving: the working
tools and Runtime are useful today, while several domain services and native
client integrations are still prototypes or planned components.

## What you can work with

- GT/Pharo inspection, debugging, examples, and Lepiter documentation.
- Catalyst Runtime workers, services, scheduling, and local execution.
- Foundation forms and Atelier tools, plus Process modelling packages.
- Catalyst Chat and its bounded explorer/maintainer tasks in the local DevKit.
- Application, simulation, ecosystem, landscape, and Unreal integration packages
  at different stages of development; evaluate each against its own evidence.

The component map also describes the intended wider platform. It does not mean
that persistent distributed models, Users, Presence, economy, every Unreal
plugin, or a Swift application template are production-ready. Current Connect,
Runtime, and Groups work has its own implementation and validation boundaries.

## Installation

Install Catalyst through [BVC](https://github.com/BenjaVisionPro/bvc#install).
With BVC installed, create and launch a local development project:

```sh
bvc init MyCatalystProject
cd MyCatalystProject
bvc run
```

BVC builds and launches the GT/Pharo DevKit without starting a GemStone deployment.
Your project's BVC configuration selects the components and startup packages.
Package-loading details below describe development inside that environment.

Use the BVC-built DevKit to develop your application or contribute to Catalyst.
The detailed component and validation notes below explain where each capability
currently stops.

## Catalyst Chat: Barry, the Catalyst Fairy

Select **Catalyst Chat** in GT's existing Chats popup, choose a connection and press **+**. Barry opens with the fairy artwork and discovers the running DevKit's image, platform, registered Catalyst projects and knowledge base.

Lepiter object-reference annotations in instructions are preserved as text, including their IDs and fallback labels. Export does not require the referenced live object to exist.

Use **Instructions** in the chat header or the **Instruction pages** inspector view to open and edit the Catalyst Lepiter pages. The working rules and role instructions are captured afresh for each user message and child task. An instruction edit applies to subsequent work, without changing a child already running.

Barry answers directly or starts a bounded **System Explorer** or **System Maintainer** task through the GT harness. Explorer has source and documentation search. Maintainer also has local code changes, examples, SUnit tests, object evaluation and Lepiter changes. Maintainer tasks require a user request for that change. Children start fresh with the parent's connection and model and have no delegation tool. Requested tools can narrow a role; unsupported models, history forks and invalid page references fail explicitly. Stop propagates to a child; timeout requests a stop and releases subscriptions.

Source development happens in the running image. Saving source files, committing and pushing are separate user-authorized actions through the DevKit's existing GT Git or Iceberg tools. Barry must not discover, copy or synchronize external checkouts. Every child receives its complete bounded task and acceptance checks.

This integration is for the privileged local DevKit. Tool composition is not a sandbox. Production mutation, remote GemStone operations, durable task resume and autonomous background maintenance are outside this release. Runtime and domain packages have no dependency on these GT classes. The abandoned `BVCAI*` experiment and its events package have been removed.

Attachments use GT's existing file classification, message objects and provider serialization. `composerSendsAttachments` checks the composer path with PNG, PDF and text files, including instruction refresh and outgoing content.

Run `BVCFairyExamples` through GT's existing example tools in the BVC-built DevKit. The examples include the actual popup selection and creation flow, instruction editing and navigation, role boundaries, result validation, cancellation and timeout. Build environments exclusively through BVC.

Repository Markdown is available through GT's existing `getDirectoryContents` and `getFilesContents` formats. Use project-relative references such as `CatalystRuntime/runtime` and `CatalystRuntime/README.md`; host filesystem paths are neither accepted nor returned. These tools list only visible directories and readable Markdown documents; they exclude hidden paths, symlinks and documents over 256 KiB. A mixed request containing any denied file is rejected before reading. Directory omissions do not establish that a file is absent.

Omit `toolNames` or supply an empty list to use a specialist's role tools. Nonempty lists select allowed subsets. Child errors, cancellation, timeout and missing responses retain an inspectable child execution; error results include its ID and preserve the original diagnostic.

MCP checkpoint, 17 October 2026: **34 examples passed, with no failures, errors or skips**, against live changes in the BVC-built GT 1.1.622 DevKit. A real Explorer delegation read the Runtime implementation plan, baseline, gap analysis and functional critique and returned a qualified T0/T1 assessment. This checkpoint does not claim another fresh BVC rebuild or native GemStone validation.

Delegation handoff checkpoint, 17 October 2026: model-based child providers now have independent model/provider and compaction bindings. The serialized request uses the child role tools; `delegatedRequestTools` checks both roles without network access. A real Maintainer used `compileMethods`, `examplesInClassesRun` and `smalltalkCodeEvaluation`, recompiled an unchanged example and passed **36/36 examples**, with no failures, errors or skips. Existing Iceberg objects provide repository status, `workingCopyDiff` and `index updateDiskWorkingCopy:` for saving a reviewed scoped diff; a separate shell or persistence tool is not required. The probe inspected these APIs without writing repository files, committing or changing Runtime. This was a live fix in the current BVC-built image; a fresh BVC rebuild remains a separate checkpoint.

## Documentation

The repo-owned DevKit book starts with **Catalyst working rules** and **Catalyst framework ownership**. Barry and both specialist roles receive these pages automatically. The separate **Catalyst Runtime** book lives in `CatalystRuntime/lepiter`; the existing `BaselineOfCatalystDevKit class >> loadLepiter` registers both books through GT. The four existing Barry instruction page identities are preserved. P0 MCP verification in the existing BVC-built image passed all 34 Barry examples, book discovery/link checks and one real Explorer delegation across both books. The Runtime book records its focused execution results and remaining proof. A fresh BVC rebuild remains a separate checkpoint. Other component documentation remains pending replacement. The obsolete `BV-Catalyst-Runtime-*` source packages have been removed from DevKit; Runtime engine source belongs to CatalystRuntime.

Start with the DevKit documentation. The TGC documentation comes after it as a concrete example of what the platform is intended to support.

### Catalyst DevKit documentation

These documents explain the platform architecture, component boundaries, runtime/deployment model, communication model, and how Catalyst capabilities support TGC without being limited to it.

- [Introduction to Catalyst](readme/catalyst-devkit/01_Catalyst_Introduction.md)
- [Catalyst DevKit — Stakeholder Overview v0.1](readme/catalyst-devkit/02_Catalyst_DevKit_Stakeholder_Overview_v0_1.md)
- [Catalyst DevKit — Architecture Principles v0.1](readme/catalyst-devkit/03_Catalyst_DevKit_Architecture_Principles_v0_1.md)
- [Catalyst DevKit — Component Map v0.1](readme/catalyst-devkit/04_Catalyst_DevKit_Component_Map_v0_1.md)
- [Catalyst DevKit — Runtime and Deployment Model v0.1](readme/catalyst-devkit/05_Catalyst_DevKit_Runtime_and_Deployment_Model_v0_1.md)
- [Catalyst DevKit — Communication Model v0.1](readme/catalyst-devkit/06_Catalyst_DevKit_Communication_Model_v0_1.md)
- [Catalyst DevKit — TGC Capability Mapping v0.1](readme/catalyst-devkit/07_Catalyst_DevKit_TGC_Capability_Mapping_v0_1.md)

### That Game: Catalyst documentation

That Game: Catalyst is a project used to explore Catalyst's direction for
persistent multiplayer worlds. These documents describe experience goals,
architecture, and proposed systems. They are not a list of features already
delivered by the DevKit or a released game.

- [TGC — Experience Pillars v0.2](readme/tgc/TGC_-_Experience_Pillars_v0.2.md)
- [TGC — Narrative Systems Brief v0.2](readme/tgc/TGC_-_Narrative_Systems_Brief_v0.2.md)
- [TGC — One-Page Executive Summary v0.1](readme/tgc/TGC_-_One-Page_Executive_Summary_v0.1.md)
- [TGC — One-Page Experience Pillars v0.1](readme/tgc/TGC_-_One-Page_Experience_Pillars_v0.1.md)
- [TGC — One-Page Vertical Slice Summary v0.1](readme/tgc/TGC_-_One-Page_Vertical_Slice_Summary_v0.1.md)
- [TGC — Stakeholder Handoff Note v0.1](readme/tgc/TGC_-_Stakeholder_Handoff_Note_v0.1.md)
- [TGC — Stakeholder Overview v0.2](readme/tgc/TGC_-_Stakeholder_Overview_v0.2.md)
- [TGC — Systems Context Brief v0.2](readme/tgc/TGC_-_Systems_Context_Brief_v0.2.md)
- [TGC — Vertical Slice Brief v0.2](readme/tgc/TGC_-_Vertical_Slice_Brief_v0.2.md)
## Connect ownership

CatalystConnect now owns the GemStone and GT/Pharo reference, CATP contract and
conformance plan. CatalystConnectCPP and CatalystConnectSwift are the other
implementations; CatalystConnectPlugin is the Unreal adapter. Implementation
readiness is tracked in the reference repository. The legacy DevKit
`BV-Catalyst-Connect-Core` remains a compatibility dependency of Store until a
separate migration; it does not define CATP or establish network support.

## License

This repository is licensed under the [Catalyst Developer License](LICENSE).

Each developer using Catalyst for development needs an active
BenjaVision-Catalyst subscription: **$5 per month, billed annually at $60 per
developer**, including access to the BenjaVision-Catalyst repository. New products,
updates, bug fixes, and recompilation require active developer subscriptions.
Automated build machines do not need separate subscriptions.

Products lawfully built during active subscriptions may continue to be used,
hosted, sold, and distributed indefinitely without runtime royalties. Customers
and operators do not need subscriptions solely to use or distribute those builds.
Commercial and proprietary products are permitted; this license does not require
you to publish your own source code.

Existing license grants and separately licensed third-party material remain
unaffected. See [LICENSE](LICENSE) for the complete terms.
