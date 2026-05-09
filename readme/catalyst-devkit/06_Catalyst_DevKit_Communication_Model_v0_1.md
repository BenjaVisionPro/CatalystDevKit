# Catalyst DevKit — Communication Model v0.1

## Communication Positioning

Catalyst systems are built for realtime, persistent, multiplayer applications. That requires communication infrastructure designed around timeliness, relevance, reliability, observability, and clean integration with server-side runtime execution.

Catalyst communication is provided through Catalyst Connect and Catalyst Presence.

## Catalyst Connect

Catalyst Connect provides realtime communication infrastructure for Catalyst systems. It connects clients, applications, Catalyst Runtime, and external systems using CATP — Catalyst Transport Protocol.

Connect owns CATP protocol behaviour, realtime message communication, connection management, message relevance windows, mixed reliability semantics, flexible encoding, protocol configuration, message-level observability, and communication between clients, apps, Runtime, and systems.

## CATP — Catalyst Transport Protocol

CATP is designed around PF4P: Perfectly Fit for Purpose.

CATP provides timeliness enforcement, message relevance windows, reliable/partially reliable/unreliable delivery classes, flexible encoding, message-level observability, telemetry for live tuning, and support for realtime system semantics.

## Message Relevance and Mixed Reliability

In realtime systems, not all messages remain valuable forever. CATP supports relevance windows so messages can be discarded when they no longer matter.

Reliable messages are used for committed model changes, economic transactions, authoritative user actions, and process state transitions.

Partially reliable messages are used for time-sensitive gameplay updates, short-lived interaction state, streaming world updates, and supersedable deltas.

Unreliable messages are used for high-frequency transient updates, preview data, non-authoritative hints, and rapidly changing spatial information.

## Catalyst Presence

Catalyst Presence owns human communication behaviour and social presence.

Connect moves system messages. Presence defines what communication means in a social world.

Presence coordinates who is present, where they are socially and spatially, which communication contexts they belong to, how audio/media should be routed, how channels are created and joined, how proximity and group communication behave, how social comfort controls apply, and how client presentation receives spatial/channel metadata.

The physical audio/media transport is handled by mediasoup v3 / libmediasoupclient, integrated behind Catalyst Presence.

## Presence and Audio Boundary

| Layer | Responsibility |
|---|---|
| Catalyst Presence | Social communication model, channel context, presence state, spatial metadata, permissions, moderation hooks, client/server behaviour |
| mediasoup / libmediasoupclient | Real-time audio/media transport |
| Catalyst Connect / CATP | Catalyst system messaging and protocol infrastructure |
| Client integration | Presentation, local audio rendering, user interface, interaction controls |

## Summary

Catalyst Connect provides realtime message infrastructure through CATP. Catalyst Presence owns presence, communication contexts, audio/media coordination, spatial metadata, moderation hooks, and social communication behaviour. mediasoup/libmediasoupclient provides underlying realtime media transport behind Presence.