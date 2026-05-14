# Catalyst DevKit — Runtime and Deployment Model v0.1

## Runtime Positioning

Catalyst Runtime is the execution foundation for Catalyst-based games and applications.

Catalyst Runtime is the server-side execution environment. All Catalyst components operate on Runtime.

During development, Runtime runs locally inside [Catalyst DevKit](../../README.md). During deployment, Runtime runs and scales on GemStone.

## Development Model

Catalyst development happens in the free [Catalyst DevKit](../../README.md).

The DevKit is built around Pharo/GToolkit and provides local Runtime execution, component execution, model inspection, runtime inspection, debugging, local integration testing, exploratory development, project-specific tooling, component tools/inspectors, and a single-application development environment.

## Deployment Model

Catalyst projects deploy to Catalyst GemStone Runtime which supports scalling for massive concurrent user bases.

GemStone provides a non-commercial licence suitable for deployment testing. Large-scale deployment uses GemStone’s commercial licence model.

## Development-To-Deployment Path

1. Install Catalyst DevKit and add the bin dirctory to your path
2. Create your project (bvc )
3. Build your Catalyst backend from the latest source daily or as needed (bvc build)
4. Launch your game server (bvc run)
5. Develop, and test your game live
6. Save source changes to repo.
7. Build your deployment environment (bvc )
8. Many updates can be pushed from the dekkit into production without bringing down the runtime.

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