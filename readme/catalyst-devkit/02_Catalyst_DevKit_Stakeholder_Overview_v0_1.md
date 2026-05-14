# Catalyst DevKit — Stakeholder Overview v0.1

## Executive Summary

[Catalyst DevKit](../../README.md) is the free development environment developers use to create Catalyst-based games and applications.

It provides a local Pharo/GToolkit runtime, model tooling, inspection, debugging, and component integration so developers can build and run Catalyst systems in one development application.

Catalyst projects run on Catalyst Runtime. During development, Runtime runs locally inside the DevKit. In deployment, Runtime runs and scales on GemStone.

Catalyst is built from focused components. Each component owns one clear area of responsibility, implements that responsibility fully, and integrates cleanly with the rest of the platform.

Unreal Engine is the first supported game client target. Catalyst components that require Unreal integration provide Unreal Engine plugins, currently purchasable through Epic’s Fab Store. The architecture should also support future community-created integrations for other engines and clients.

## Core Components

Catalyst Foundation provides base model classes and shared conventions.

Catalyst Runtime is the server-side execution framework. All Catalyst components operate on Runtime.

Catalyst Model provides the distributed object model, persistent object state, transactional model changes, and synchronisation between Runtime and connected clients.

Catalyst Connect provides realtime communication infrastructure using CATP — Catalyst Transport Protocol.

Catalyst Presence owns presence, audio/media coordination, communication contexts, channel state, spatial metadata, moderation hooks, and client/server social communication behaviour. The underlying media transport is mediasoup v3 / libmediasoupclient.

Catalyst Users represents people, identities, accounts, preferences, sessions, and user records.

Catalyst Groups represents groups of people and relationships between them.

Catalyst Process manages structured process execution for missions, jobs, approvals, auctions, governance flows, crafting processes, settlement tasks, and other workflows.

Catalyst Simulation provides a generic simulation environment. Catalyst Ecosystem is an ecosystem simulation built using Catalyst Simulation.

Catalyst Landform provides distributed persistent landscape editing, initially presented in Unreal Engine using Voxel Plugin Pro.

Catalyst Architect provides persistent collaborative building.

Catalyst Economy provides currencies, exchanges, wallets, banks, payment systems, trade, auctions, and economic business models and processes.

CatalystApp provides a Swift application template for Catalyst apps on iOS, macOS, tvOS, and watchOS.

## TGC as Proof of Catalyst Ideals

That Game: Catalyst is proof of the Catalyst ideals. It demonstrates how Catalyst components combine to support a persistent, social, multiplayer world with communication, shared presence, distributed state, simulation, building, terrain editing, economy, processes, users, groups, and long-form world behaviour.