# Catalyst DevKit

Catalyst DevKit is a free development environment for building Catalyst-based games and applications.

It is designed for developers who want to build persistent, social, multiplayer systems without turning every project into a one-off backend, networking stack, object model, and tooling problem.

Catalyst projects are built from small, focused parts that work together. Each part has a clear job: storing shared world state, running server-side behaviour, moving realtime messages, managing users and groups, coordinating presence, or connecting to a game client. Unreal Engine is the first supported game client, and the platform is designed so other clients and tools can be added over time.

Catalyst DevKit is where developers build their game backend. It provides a local Pharo/GToolkit environment where the game’s server-side models, behaviours, processes, simulations, and integrations can run together in one application. Developers can inspect live objects, debug runtime behaviour, test integrations, and build locally before deploying to GemStone-backed Runtime environments.

The same environment can also be used to contribute to Catalyst itself, but its first job is helping developers build their own Catalyst-based games and applications.

That Game: Catalyst (TGC) is included in this documentation as the proof implementation for the Catalyst ideals: a persistent multiplayer social world built around presence, communication, shared agency, player-shaped environments, simulation, economy, and long-running world behaviour.

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

## Documentation

Start with the DevKit documentation. The TGC documentation comes after it as a concrete example of what the platform is intended to support.

### Catalyst DevKit documentation

These documents explain the platform architecture, component boundaries, runtime/deployment model, communication model, and how Catalyst capabilities support TGC without being limited to it.

- [Catalyst DevKit — Stakeholder Documentation Pack v0.1](readme/catalyst-devkit/00_Catalyst_DevKit_Stakeholder_Documentation_Pack_v0_1.md)
- [Catalyst DevKit — Source Document Audit v0.1](readme/catalyst-devkit/01_Catalyst_DevKit_Source_Document_Audit_v0_1.md)
- [Catalyst DevKit — Stakeholder Overview v0.1](readme/catalyst-devkit/02_Catalyst_DevKit_Stakeholder_Overview_v0_1.md)
- [Catalyst DevKit — Architecture Principles v0.1](readme/catalyst-devkit/03_Catalyst_DevKit_Architecture_Principles_v0_1.md)
- [Catalyst DevKit — Component Map v0.1](readme/catalyst-devkit/04_Catalyst_DevKit_Component_Map_v0_1.md)
- [Catalyst DevKit — Runtime and Deployment Model v0.1](readme/catalyst-devkit/05_Catalyst_DevKit_Runtime_and_Deployment_Model_v0_1.md)
- [Catalyst DevKit — Communication Model v0.1](readme/catalyst-devkit/06_Catalyst_DevKit_Communication_Model_v0_1.md)
- [Catalyst DevKit — TGC Capability Mapping v0.1](readme/catalyst-devkit/07_Catalyst_DevKit_TGC_Capability_Mapping_v0_1.md)

### That Game: Catalyst documentation

These documents explain the social-world game that proves the Catalyst ideals. They describe the player experience, stakeholder framing, systems context, narrative model, and vertical slice that the Catalyst components are designed to support.

- [TGC Stakeholder Documentation Pack](readme/tgc/README.md)
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
