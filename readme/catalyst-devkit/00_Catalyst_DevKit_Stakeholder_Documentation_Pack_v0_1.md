# Catalyst DevKit — Stakeholder Documentation Pack v0.1

## Project Centre

[Catalyst DevKit](../../README.md) is the free development environment developers use to create Catalyst-based games and applications.

It provides a local Pharo/GToolkit runtime, model tooling, inspection, debugging, and component integration so developers can build and run Catalyst systems in one development application.

Catalyst projects run on Catalyst Runtime. During development, Runtime runs locally inside the DevKit. In deployment, Runtime runs and scales on GemStone.

The platform is built from focused Catalyst components. Each component has one clear responsibility, implements that responsibility fully, and integrates cleanly with the rest of the platform.

## Documentation Set

1. [Catalyst DevKit](../../README.md) — Source Document Audit
2. [Catalyst DevKit — Stakeholder Overview](02_Catalyst_DevKit_Stakeholder_Overview_v0_1.md)
3. [Catalyst DevKit — Architecture Principles](03_Catalyst_DevKit_Architecture_Principles_v0_1.md)
4. [Catalyst DevKit — Component Map](04_Catalyst_DevKit_Component_Map_v0_1.md)
5. [Catalyst DevKit — Runtime and Deployment Model](05_Catalyst_DevKit_Runtime_and_Deployment_Model_v0_1.md)
6. [Catalyst DevKit — Communication Model](06_Catalyst_DevKit_Communication_Model_v0_1.md)
7. [Catalyst DevKit — TGC Capability Mapping](07_Catalyst_DevKit_TGC_Capability_Mapping_v0_1.md)

## Commercial and Deployment Position

[Catalyst DevKit](../../README.md) is free. Developers can use it to build, inspect, test, and run Catalyst-based projects locally.

GemStone provides a non-commercial licence suitable for deployment testing. Large-scale deployment uses GemStone’s commercial licence model.

For now, Catalyst Unreal Engine plugins are purchasable through Epic’s Fab Store. Connect and Model may be included for free in the future, but current stakeholder language should assume UE plugins are paid unless explicitly stated otherwise.

## Final Positioning

[Catalyst DevKit](../../README.md) gives developers a free local development environment for building Catalyst-based games and applications from focused components.

Catalyst Runtime provides execution. Catalyst Model provides distributed persistent state. Catalyst Connect provides realtime system messaging through CATP. Catalyst Presence owns social communication and audio/media coordination. Other Catalyst components provide focused capabilities for people, groups, processes, simulations, ecosystems, landscapes, buildings, economies, apps, and client integrations.