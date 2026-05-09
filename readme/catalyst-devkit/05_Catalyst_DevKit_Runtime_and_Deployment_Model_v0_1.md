# Catalyst DevKit — Runtime and Deployment Model v0.1

## Runtime Positioning

Catalyst Runtime is the execution foundation for Catalyst-based games and applications.

Catalyst Runtime is the server-side execution environment. All Catalyst components operate on Runtime.

During development, Runtime runs locally inside [Catalyst DevKit](../../README.md). During deployment, Runtime runs and scales on GemStone.

## Development Model

Catalyst development happens in the free [Catalyst DevKit](../../README.md).

The DevKit is built around Pharo/GToolkit and provides local Runtime execution, component execution, model inspection, runtime inspection, debugging, local integration testing, exploratory development, project-specific tooling, component tools/inspectors, and a single-application development environment.

## Deployment Model

Catalyst projects deploy to Catalyst Runtime environments backed by GemStone.

Deployment supports persistent object state, server-side execution, transactional model changes, distributed runtime behaviour, multi-user operation, scaling beyond local development, deployment testing, and large-scale commercial deployment.

GemStone provides a non-commercial licence suitable for deployment testing. Large-scale deployment uses GemStone’s commercial licence model.

## Development-To-Deployment Path

1. Model locally using Catalyst Foundation conventions.
2. Run Catalyst Runtime inside the DevKit.
3. Load and test required Catalyst components together.
4. Inspect models, runtime state, component state, and process execution.
5. Connect clients through Catalyst Connect and component integrations.
6. Test deployment with GemStone’s non-commercial licence where suitable.
7. Move to GemStone’s commercial licence model for production scale.

## Runtime Authority

Catalyst Runtime owns authoritative model changes, component execution, process execution, simulation execution, server-side validation, scheduled and long-running work, coordination between components, Model integration, and Connect integration.

Clients present and interact with Catalyst systems. Clients should not own authoritative persistent state unless explicitly designed to do so.

## Model and Transaction Flow

1. A client requests or triggers an action.
2. Catalyst Connect carries the relevant message to Runtime.
3. Runtime executes the appropriate component behaviour.
4. Catalyst Model applies transactional model changes.
5. Relevant clients receive synchronised model updates.
6. Client presentation updates accordingly.

## Summary

Build locally, inspect deeply, integrate components cleanly, deploy to GemStone, and scale without changing the fundamental architecture.