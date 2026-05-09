# Catalyst Documentation

This repository contains stakeholder documentation for **Catalyst DevKit** and **That Game: Catalyst (TGC)**.

## Project framing

**Catalyst DevKit** is the free development environment developers use to create Catalyst-based games and applications. Catalyst components run on Catalyst Runtime, use Catalyst Model for distributed persistent state, use Catalyst Connect/CATP for realtime system messaging, and integrate with clients through focused plugins or application frameworks.

**TGC** is a multiplayer social world built around presence, communication, shared agency, and player-shaped civilisation. It is proof of the Catalyst ideals: focused components working together to support persistent social-world gameplay.

## Documentation

### Start here

- [Documentation Index](readme/README.md)

### Catalyst DevKit stakeholder documentation

Catalyst DevKit is the developer-facing foundation of the Catalyst platform. These documents describe the component model, runtime and deployment approach, communication model, architecture principles, and how Catalyst capabilities support TGC without being limited to TGC.

- [Catalyst DevKit — Stakeholder Documentation Pack v0.1](readme/catalyst-devkit/00_Catalyst_DevKit_Stakeholder_Documentation_Pack_v0_1.md)
- [Catalyst DevKit — Source Document Audit v0.1](readme/catalyst-devkit/01_Catalyst_DevKit_Source_Document_Audit_v0_1.md)
- [Catalyst DevKit — Stakeholder Overview v0.1](readme/catalyst-devkit/02_Catalyst_DevKit_Stakeholder_Overview_v0_1.md)
- [Catalyst DevKit — Architecture Principles v0.1](readme/catalyst-devkit/03_Catalyst_DevKit_Architecture_Principles_v0_1.md)
- [Catalyst DevKit — Component Map v0.1](readme/catalyst-devkit/04_Catalyst_DevKit_Component_Map_v0_1.md)
- [Catalyst DevKit — Runtime and Deployment Model v0.1](readme/catalyst-devkit/05_Catalyst_DevKit_Runtime_and_Deployment_Model_v0_1.md)
- [Catalyst DevKit — Communication Model v0.1](readme/catalyst-devkit/06_Catalyst_DevKit_Communication_Model_v0_1.md)
- [Catalyst DevKit — TGC Capability Mapping v0.1](readme/catalyst-devkit/07_Catalyst_DevKit_TGC_Capability_Mapping_v0_1.md)

### That Game: Catalyst stakeholder documentation

That Game: Catalyst is the proof implementation for the Catalyst ideals. These documents describe the TGC player experience, social-world foundation, narrative systems, vertical slice, and stakeholder framing that Catalyst components are intended to support.

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

## Repository layout

```text
.
├── README.md
└── readme
    ├── README.md
    ├── catalyst-devkit
    └── tgc
```

## Documentation principles

- Use **component** for Catalyst capability areas.
- Use **plugin** only for client or engine-specific integration packages.
- Keep stakeholder language direct, technical, and matter-of-fact.
- Avoid retired terminology unless explicitly writing an audit or migration note.
- Keep each component focused, complete, and cleanly integrated.
