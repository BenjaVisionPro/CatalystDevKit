# Catalyst DevKit

Catalyst DevKit is for developers who want to build persistent multiplayer games without reinventing the entire backend every time.

Most ambitious multiplayer projects eventually run into the same wall: shared state, server authority, realtime messaging, users, groups, presence, simulation, tooling, deployment, and debugging all become their own projects. Then the game starts competing with its own infrastructure.

Catalyst DevKit exists to change that.

It gives you a local development environment where you build your game’s backend, inspect live objects, run server-side behaviour, test integrations, and shape the systems your game depends on before deploying to scale.

It is not magic. It is not a shortcut around hard problems. It is a way to face those hard problems with structure instead of panic.

Catalyst is built from focused parts that do clear jobs and work together: persistent models, runtime execution, realtime messaging, presence, users, groups, processes, simulation, economies, landscapes, buildings, and client integrations.

Start small. Build locally. Inspect everything. Scale when it earns it.

That is the point.

Catalyst DevKit can also be used to contribute to Catalyst itself, but its first job is helping developers build their own Catalyst-backed games and applications.

That Game: Catalyst (TGC) is mentioned here as an exemplar of Catalyst ideals: a persistent multiplayer social world built around presence, communication, shared agency, player-shaped environments, simulation, economy, and long-running world behaviour.

## What Catalyst DevKit provides

- Local Catalyst Runtime for development
- Distributed object modelling through Catalyst Model
- Realtime system messaging through Catalyst Connect and CATP
- Presence, channel context, and media coordination through Catalyst Presence
- User and group modelling
- Process execution for long-running workflows
- Simulation and ecosystem modelling
- Persistent landscape and building systems
- Economy systems
- Unreal Engine integration points
- Swift application templates through CatalystApp
- Inspection, debugging, and development tooling through Pharo/GToolkit

## Catalyst Chat: Barry, the Catalyst Fairy

Select **Catalyst Chat** in GT's existing Chats popup, choose a connection and press **+**. Barry opens with the fairy artwork and discovers the running DevKit's image, platform, registered Catalyst projects and knowledge base.

Use **Instructions** in the chat header or the **Instruction pages** inspector view to open and edit the Catalyst Lepiter pages. The working rules and role instructions are captured afresh for each user message and child task. An instruction edit applies to subsequent work, without changing a child already running.

Barry answers directly or starts a bounded **System Explorer** or **System Maintainer** task through the GT harness. Explorer has source and documentation search. Maintainer also has local code changes, examples, SUnit tests, object evaluation and Lepiter changes. Maintainer tasks require a user request for that change. Children start fresh with the parent's connection and model and have no delegation tool. Requested tools can narrow a role; unsupported models, history forks and invalid page references fail explicitly. Stop propagates to a child; timeout requests a stop and releases subscriptions.

Source development happens in the running image. Saving source files, committing and pushing are separate user-authorized actions through the DevKit's existing GT Git or Iceberg tools. Barry must not discover, copy or synchronize external checkouts. Every child receives its complete bounded task and acceptance checks.

This integration is for the privileged local DevKit. Tool composition is not a sandbox. Production mutation, remote GemStone operations, durable task resume and autonomous background maintenance are outside this release. Runtime and domain packages have no dependency on these GT classes. The abandoned `BVCAI*` experiment and its events package have been removed.

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

- [Catalyst DevKit — Stakeholder Overview v0.1](readme/catalyst-devkit/02_Catalyst_DevKit_Stakeholder_Overview_v0_1.md)
- [Catalyst DevKit — Architecture Principles v0.1](readme/catalyst-devkit/03_Catalyst_DevKit_Architecture_Principles_v0_1.md)
- [Catalyst DevKit — Component Map v0.1](readme/catalyst-devkit/04_Catalyst_DevKit_Component_Map_v0_1.md)
- [Catalyst DevKit — Runtime and Deployment Model v0.1](readme/catalyst-devkit/05_Catalyst_DevKit_Runtime_and_Deployment_Model_v0_1.md)
- [Catalyst DevKit — Communication Model v0.1](readme/catalyst-devkit/06_Catalyst_DevKit_Communication_Model_v0_1.md)
- [Catalyst DevKit — TGC Capability Mapping v0.1](readme/catalyst-devkit/07_Catalyst_DevKit_TGC_Capability_Mapping_v0_1.md)

### That Game: Catalyst documentation

That Game: Catalyst is not trying to be another giant checklist of survival, crafting, building, economy, factions, combat, and lore.

It has those things. But they are not the point.

The point is people.

TGC is a multiplayer social world built around presence, communication, shared agency, and player-shaped civilisation. It starts from a simple idea: games feel better when being with other people feels natural.

So the foundation is clean directional sound, proximity-aware communication, comfortable social spaces, and systems that give players real reasons to talk, build, explore, trade, argue, organise, repair, discover, and come back.

The world is sci-fi. The systems are ambitious. The mystery is long. The technology underneath is serious.

But the test is simple:

Do players want to stay in the world after the objective is done?

If the answer is yes, we are building the right thing.

TGC is proof of the Catalyst ideals: focused technology supporting a world that feels social, persistent, strange, useful, and worth inhabiting.

No fake revolution. No “metaverse” perfume cloud.

Just a game world where people might actually want to spend time together.

TGC intends to live up to it's byline... A reasonably fun game, that pretty much doesn't suck.

- [TGC — Experience Pillars v0.2](readme/tgc/TGC_-_Experience_Pillars_v0.2.md)
- [TGC — Narrative Systems Brief v0.2](readme/tgc/TGC_-_Narrative_Systems_Brief_v0.2.md)
- [TGC — One-Page Executive Summary v0.1](readme/tgc/TGC_-_One-Page_Executive_Summary_v0.1.md)
- [TGC — One-Page Experience Pillars v0.1](readme/tgc/TGC_-_One-Page_Experience_Pillars_v0.1.md)
- [TGC — One-Page Vertical Slice Summary v0.1](readme/tgc/TGC_-_One-Page_Vertical_Slice_Summary_v0.1.md)
- [TGC — Stakeholder Documentation Pack v0.3](readme/tgc/TGC_-_Stakeholder_Documentation_Pack_v0.3.md)
- [TGC — Stakeholder Handoff Note v0.1](readme/tgc/TGC_-_Stakeholder_Handoff_Note_v0.1.md)
- [TGC — Stakeholder Overview v0.2](readme/tgc/TGC_-_Stakeholder_Overview_v0.2.md)
- [TGC — Systems Context Brief v0.2](readme/tgc/TGC_-_Systems_Context_Brief_v0.2.md)
- [TGC — Vertical Slice Brief v0.2](readme/tgc/TGC_-_Vertical_Slice_Brief_v0.2.md)