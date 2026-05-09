# Catalyst DevKit — TGC Capability Mapping v0.1

## Purpose

That Game: Catalyst is proof of the Catalyst ideals.

TGC demonstrates how focused Catalyst components combine to support a persistent, social, multiplayer world built around presence, communication, shared agency, player-shaped environments, simulation, economy, and long-running world behaviour.

## TGC Experience Foundation

TGC is built around one core experience: players feel present with each other in a world they can understand, shape, and care about.

That experience requires Catalyst support for realtime communication, social presence, users and groups, persistent world state, distributed object modelling, server-side execution, player-shaped terrain, player-built structures, structured processes, simulation, ecology, economy, client integration, and development tooling.

## Capability Map Summary

| TGC Capability | Primary Catalyst Component | Supporting Components |
|---|---|---|
| Local development and tooling | Catalyst DevKit | CF, CR, CM, CC, all components |
| Server-side execution | Catalyst Runtime | CM, CC, CP, CS, CE |
| Shared persistent state | Catalyst Model | CF, CR, CC |
| Realtime system messaging | Catalyst Connect | CR, CM, Presence |
| Player identity | Catalyst Users | CG, Presence, CM |
| Social groups and organisations | Catalyst Groups | CU, Presence, CE, CP |
| Social presence and communication | Catalyst Presence | CU, CG, CC, mediasoup, UE plugin |
| Landscape editing | Catalyst Landform | CM, CR, CC, CS:E, UE/Voxel Plugin Pro |
| Persistent building | Catalyst Architect | CM, CR, CG, CL, CP, CE |
| Process-driven gameplay | Catalyst Process | CR, CM, CU, CG, CE, CS |
| Simulation | Catalyst Simulation | CR, CM, CP |
| Ecosystem simulation | Catalyst Ecosystem | CS, CL, CM, CR |
| Economy | Catalyst Economy | CU, CG, CP, CM, CR |
| Apple ecosystem apps | CatalystApp | CC, CM, CU, Presence |
| Unreal game client | Catalyst Unreal plugins | CC, CM, Presence, CL, CA |

## Capability Areas Required By TGC But Not Yet Confirmed As First-Class Components

| Capability Area | Required For TGC | Possible Ownership |
|---|---|---|
| Inventory and items | resources, loot, equipment, crafting, trade | dedicated component or Model + Economy + Process |
| Resources | mining, gathering, scarcity, crafting inputs | dedicated component or CS:E / Economy / Landform integration |
| Crafting | recipes, production, proficiency, projects | dedicated component or Process + Economy + Items |
| Infrastructure and power | settlement operation, repair, automation | dedicated component or Architect + Process + Simulation |
| Governance | laws, votes, settlement decisions, permissions | dedicated component or Groups + Process + Economy |
| Reputation | factions, trust, trade, social standing | dedicated component or Users + Groups + Process |
| Settlements | persistent social places and services | dedicated component or Groups + Architect + Landform + Economy |
| Missions | structured gameplay objectives | dedicated component or Process + game-specific model |
| Progression | levels, skills, expertise, mastery | dedicated component or Users + Process + game-specific model |
| Combat | PvE/PvP authority, damage, encounters | dedicated component or game-specific runtime systems |
| Discovery | scans, POIs, knowledge unlocks, artefacts as discoveries | dedicated component or Process + Model + game-specific systems |
| Observability | telemetry, diagnostics, operations | platform-wide capability across components |

## Vertical Slice Capability Mapping

| Vertical Slice Need | Catalyst Support |
|---|---|
| local development | Catalyst DevKit |
| server-side authority | Catalyst Runtime |
| persistent local world state | Catalyst Model |
| realtime messaging | Catalyst Connect / CATP |
| player identity | Catalyst Users |
| group/session context | Catalyst Groups + Presence |
| proximity/directional voice | Catalyst Presence + mediasoup + UE plugin |
| settlement space | Catalyst Architect + game-specific settlement model |
| repair/build interaction | Catalyst Architect + Process |
| basic resources | resource capability area |
| simple crafting/repair | crafting capability area + Process |
| nearby terrain/anomaly | Catalyst Landform |
| environmental/ecological context | Catalyst Ecosystem where required |
| VERITAS/Harmony interaction | game-specific AI/narrative systems over Runtime/Model/Process |
| mystery clue / record contradiction | discovery/narrative capability over Model/Process |
| visible world-state change | Model + Runtime + relevant component |
| Unreal presentation | Catalyst UE plugins |

## Summary

TGC depends on Catalyst DevKit because it needs focused components that work together without collapsing into a monolithic game-specific implementation.

TGC proves the Catalyst ideals by showing how these components combine into a persistent social-world game where communication, shared presence, world shaping, simulation, economy, and structured processes reinforce each other.
