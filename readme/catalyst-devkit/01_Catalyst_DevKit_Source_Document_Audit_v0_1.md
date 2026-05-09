# Catalyst DevKit — Source Document Audit v0.1

## Audit Purpose

The existing Catalyst Plugins document is useful as historical source material, but it no longer reflects the current Catalyst DevKit architecture.

Catalyst DevKit is the free development environment developers use to create Catalyst-based games and applications.

Catalyst components run on Catalyst Runtime. In development, the DevKit provides a local Pharo/GToolkit runtime so all Catalyst components can run together in one application. In deployment, Catalyst projects run and scale on GemStone.

Unreal Engine integration is provided through purchasable UE plugins distributed through Epic’s Fab Store. Connect and Model may be included for free in the future, but for now all UE plugins should be treated as purchasable.

## What The Old Document Gets Right

The old document correctly identifies real-time communication, distributed object storage/synchronisation, user/account management, group/organisation management, economic systems, persistent landscape editing, multiplayer building, and Unreal Engine integration as important capability areas.

## Updated Framing

Use component for Catalyst system responsibilities. Use plugin only for engine-specific integration packages.

Catalyst Runtime is the server-side execution environment. All components run on Catalyst Runtime. In development, Runtime runs locally inside DevKit. In deployment, projects run and scale on GemStone.

Catalyst Model provides the distributed object model, transactional model changes, and synchronisation between Catalyst Runtime and connected clients.

Catalyst Connect uses CATP — Catalyst Transport Protocol. CATP is designed for realtime distributed systems that need purpose-built communication semantics rather than generic transport compromises.

Use Catalyst Users, Catalyst Groups, and Catalyst Economy. Economy replaces the narrower Currency framing and includes currencies, exchanges, wallets, banks, payment systems, auctions, and economic business models.

Unreal Engine is the first supported game client, but Catalyst DevKit should not be framed as Unreal-only.

## Missing Areas In The Old Documentation

The old documentation does not adequately cover Catalyst DevKit as the free developer tool, local Pharo/GToolkit runtime, GemStone deployment and scaling, Catalyst Runtime, Catalyst Foundation, Catalyst Model, CATP, Catalyst Presence, Catalyst Process, Catalyst Simulation, CS:E, CatalystApp, component boundaries, commercial model, client-agnostic future direction, or TGC as proof of Catalyst ideals.

## Recommended Rewrite Direction

The rewritten stakeholder pack should include Stakeholder Overview, Architecture Principles, Component Map, Runtime and Deployment Model, Communication Model, and TGC Capability Mapping.
