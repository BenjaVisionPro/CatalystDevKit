# Catalyst DevKit — Component Map v0.1

## Component Model

[Catalyst DevKit](../../README.md) is built around focused components. Each component owns a specific capability area, implements that capability coherently, and integrates with other Catalyst components through clear model, runtime, communication, or client-facing boundaries.

Component means the Catalyst capability area. Plugin means a client or engine-specific integration package.

## Component Layers

1. Development layer — [Catalyst DevKit](../../README.md).
2. Core platform layer — Catalyst Foundation, Runtime, Model, Connect.
3. People and social layer — Users, Groups, Presence.
4. Process and simulation layer — Process, Simulation, Ecosystem.
5. World and application layer — Landform, Architect, Economy, CatalystApp.
6. Client integration layer — Unreal plugins and future client integrations.

## Confirmed Components

[Catalyst DevKit](../../README.md): free development environment with local runtime, inspection, debugging, tooling, and integration.

Catalyst Foundation: base model classes and shared conventions.

Catalyst Runtime: server-side execution framework and authority surface.

Catalyst Model: distributed object model, persistent model state, transactional changes, and synchronisation.

Catalyst Connect: realtime communication infrastructure using CATP.

Catalyst Presence: presence, communication context, audio/media coordination, channel state, spatial metadata, and social comfort behaviour.

Catalyst Users: people, identities, accounts, preferences, sessions, and user records.

Catalyst Groups: groups, memberships, roles, organisations, shared ownership, and social structures.

Catalyst Process: process definitions, instances, transitions, tasks, approvals, time/event driven progression, and process history.

Catalyst Simulation: generic simulation environment running on Runtime.

Catalyst Ecosystem: ecosystem simulator built using Catalyst Simulation.

Catalyst Landform: distributed persistent landscape editing and Unreal/Voxel Plugin Pro presentation integration.

Catalyst Architect: persistent collaborative building.

Catalyst Economy: currencies, exchanges, wallets, banks, trade, payment systems, auctions, economic transactions, and auditability.

CatalystApp: Swift application template for Catalyst apps on Apple devices.

Catalyst Unreal integrations: engine plugins for client-side presentation and interaction.

## Capability Areas Required By TGC But Not Yet Confirmed As First-Class Components

Inventory and items, resources, crafting, infrastructure and power, governance, reputation, settlements, missions, progression, combat, discovery, and observability.

These capability areas are required by TGC, but should not be presented as confirmed first-class components until ownership is formally assigned.