# NaughtyBot

Unreal Engine **5.8** Blueprint project (also known as *One More Sphere*): a third-person arena about **gambling addiction** — drones hunt you, floors fall out from under you, and every sphere is a bet.

## Requirements

- [Unreal Engine 5.8](https://www.unrealengine.com/)
- Windows (project ships with DX12 / SM6 defaults)

No C++ module is required — open and play as a Blueprint-only project.

## Getting started

1. Install **UE 5.8** via the Epic Games Launcher.
2. Double-click `NaughtyBot.uproject` (or open it from the Launcher).
3. Press **Play** — the game boots to the **main menu** (`MainMenu`).

| Map | Role |
|-----|------|
| `Content/Maps/MainMenu` | Default / editor startup map |
| `Content/Maps/NaughtMap` | Primary gameplay level |
| `Content/Maps/TestingLevel` | Scratch / test arena |

Player-facing copy you can paste into a Help UI: see [`HELP.md`](HELP.md).

## How to play

### Theme

You’re stuck in a loop of risk. Magic balls litter the floor like chips on a table — heal when you can, roll orange and blue when you can’t help yourself. The drones and the dropping floors are the house edge.

### Controls

Same as the Third Person game mode / character:

| Action | Keyboard & Mouse | Gamepad |
|--------|------------------|---------|
| Move | **W A S D** | Left stick |
| Look | **Mouse** | Right stick |
| Jump | **Space** | A / Cross |

Input assets live under `Content/Input/` (`IA_Move`, `IA_Look`, `IA_Jump`, `IMC_Default`).

### Magic balls (spheres)

| Color | Role | Blueprint | What happens |
|-------|------|-----------|--------------|
| **Green** | Heal | `BP_HealingSphere` | Restores health |
| **Orange** | Destroy drone | `BP_DestroyDroneSphere` | Chance to **destroy a random drone**, or (via `CreateInsteadOfDestroyPercentage`) **spawn a new one** instead |
| **Blue** | Ally | `BP_SpawnAllySphere` | Chance to **spawn an ally**, or **destroy a random ally** instead |

### Death & possession

Drones fire blaster beams (`BP_BlasterBeam`). When your pawn dies, you **possess another living ally** if one remains. You’re only fully out when the last pawn is gone.

### Falling floors

`BP_DroppingFloor` pieces start giving way at the **beginning of a round** — keep moving or fall with the bet.

## Project layout

```
NaughtyBot/
├── Config/                 # Engine, input, game settings
├── Content/
│   ├── BluePrints/         # Drone, spheres, floors, menu
│   ├── GameModes/          # Including GM_MainMenu
│   ├── Maps/               # MainMenu, NaughtMap, TestingLevel, …
│   ├── ThirdPerson/        # Character, controller, default game mode
│   ├── Widgets/            # Main menu UI (WD_MainMenu, …)
│   └── …                   # Assets, input, prototyping, starter content
├── HELP.md                 # In-game / store help text
└── NaughtyBot.uproject
```

Default gameplay GameMode: `BP_ThirdPersonGameMode`  
Main menu GameMode: `GM_MainMenu`

## Notes

- Intermediate editor folders (`Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`) are gitignored.
- Large binary assets (`.uasset` / `.umap`) live under `Content/` and should be handled with Git LFS or similar if you scale source control.
