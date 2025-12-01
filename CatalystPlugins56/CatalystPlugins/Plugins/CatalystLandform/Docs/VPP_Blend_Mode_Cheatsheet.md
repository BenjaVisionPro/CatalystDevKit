# VPP Blend Mode Cheatsheet (Height & Volume)

**Scope**: This page summarizes the blend knobs your stamps use when a **StackLayer** is sampled by the **Mesher**. It’s grounded in the enums and utility functions present in your codebase.

---

## 1) Where these are used (context)
- **RenderSubsystem → RenderTree → Mesher → Query → Layer → StampWrapper → StampRuntime → BlendModeUtilities → Buffers → Mesh → Render**  
- The *runtime* stamp calls a blend helper to combine the **existing buffer value** with the **stamp’s contribution**.

---

## 2) Height Blend

### Enum
```cpp
enum class EVoxelHeightBlendMode : uint8 {
  Max,    // prefer higher outcome
  Min,    // prefer lower outcome
  Override// replace with stamp value
};
```

### Utility (selector)
```cpp
float FVoxelBlendModeUtilities::ComputeHeight(
  const FVoxelHeightTransform& StampToQuery,
  float OldHeight, float Height, const FVector2D& Position,
  EVoxelHeightBlendMode BlendMode,
  bool bApplyOnVoid,
  float Smoothness,
  float* OutAlpha /*optional*/
);
```

### Notes
- **StampToQuery**: provides min/max clamps & coordinate transform for safety/limits.
- **bApplyOnVoid**: controls whether empty/void areas are affected.
- **Smoothness**: controls how sharply the transition occurs (useful for non‑hard edges).
- **OutAlpha**: optional; the callee can return the effective blend factor used.

---

## 3) Volume (SDF) Blend

### Enum
```cpp
enum class EVoxelVolumeBlendMode : uint8 {
  Additive,    // adds material (union‑like)
  Subtractive, // removes material (difference‑like)
  Intersect,   // keeps overlap (intersection‑like)
  Override     // replace with stamp distance locally
};
```

### Utility (selector)
```cpp
float FVoxelBlendModeUtilities::ComputeDistance(
  const FVoxelVolumeTransform& StampToQuery,
  float OldDistance, float Distance,
  EVoxelVolumeBlendMode BlendMode,
  bool bApplyOnVoid,
  float Smoothness,
  float* OutAlpha /*optional*/
);
```

### Notes
- **OldDistance**/**Distance** follow your SDF sign convention; the helper applies the blend mode and returns the new distance.
- **bApplyOnVoid** & **Smoothness** behave analogously to height, but for SDFs.
- **Override** is a hard handover to the stamp’s SDF (still subject to transform bounds).

---

## 4) Quick wiring reference
- **Layers** enumerate stamps via their **StampTree** (per LOD).
- For each candidate:
  1. **StampWrapper::Apply(...)** invokes the **runtime** stamp.
  2. The runtime calls the **ComputeHeight/ComputeDistance** helper to blend into the working buffers (height or distance).  
  3. Surface types & metadata are handled alongside, subject to behavior flags.
- Validation/breadcrumb toggles in wrappers can assert invariants (e.g., untouched channels remain unchanged) and log pre/post apply.

---

## 5) Practical tips
- Prefer **Min/Max** for natural height priority decisions (ridges vs. basins).
- Use **Override** when a stamp should dictate the local shape outright.
- In SDF work, **Additive/Subtractive/Intersect** map neatly to union/difference/intersection‑style operations for compositing shapes.
- Tweak **Smoothness** to avoid aliasing or hard seams; lower values are crisper, higher values transition more gradually.
- **bApplyOnVoid** is a surgical switch—enable only when it’s intentional to alter empty areas.

---

## 6) Minimal checklist (copy/paste back to me later)
- Height: `EVoxelHeightBlendMode::{Max, Min, Override}` → `FVoxelBlendModeUtilities::ComputeHeight(...)`
- Volume: `EVoxelVolumeBlendMode::{Additive, Subtractive, Intersect, Override}` → `FVoxelBlendModeUtilities::ComputeDistance(...)`
- Wrappers call runtime → runtime calls utilities → buffers updated.
- Transform clamps, Smoothness, bApplyOnVoid, and optional OutAlpha influence the result.
