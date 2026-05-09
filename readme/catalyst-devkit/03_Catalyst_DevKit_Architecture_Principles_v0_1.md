# Catalyst DevKit — Architecture Principles v0.1

## Core Principle

[Catalyst DevKit](../../README.md) exists to help developers build Catalyst-based games and applications from focused components that work cleanly together.

Catalyst is not a monolithic engine and not a loose collection of plugins. It is a component platform built around shared model semantics, server-side runtime execution, realtime communication, local development tooling, and scalable deployment.

Each Catalyst component has one clear focus, implements that focus fully, and integrates cleanly with the rest of the Catalyst platform.

## Principles

1. Single-focus components. Each Catalyst component should own one clear capability area.
2. Complete responsibility. A component should provide a complete implementation of its focus.
3. Clean integration points. Components should enhance each other through explicit integration points.
4. Runtime-first design. Catalyst Runtime is the execution foundation for Catalyst projects.
5. Distributed model foundation. Catalyst Model provides persistent object state, transactional model changes, and synchronisation.
6. Develop locally, deploy at scale. DevKit runs Runtime locally; deployed projects run and scale on GemStone.
7. Client-agnostic core, focused client integrations. Unreal plugins are integrations, not the components themselves.
8. Purpose-built realtime communication. Catalyst Connect uses CATP, designed around PF4P: Perfectly Fit for Purpose.
9. Observable by design. Systems should be inspectable, measurable, and debuggable.
10. TGC proves the ideals without owning them. Catalyst should satisfy TGC requirements without hard-coding TGC assumptions into the platform.

## Summary

Together, these principles keep Catalyst modular without making it fragmented, scalable without making it inaccessible, and powerful without becoming a monolithic engine.