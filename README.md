# GamblingAddiction

## ❤️ Support the Developer

If you enjoyed the game and would like to support my work, you can do so here:

**InstaPay:** `+201154002675`

**PayPal:** @mazenelgayar  
https://www.paypal.me/mazenelgayar

Every bit of support helps me continue learning Unreal Engine and building bigger, better games. Thank you! ❤️

---

## 🎮 Download

https://drive.google.com/drive/folders/14ROhFKIyS6IOJZoCPvn69tL3JJFDgbiY

---

## 👨‍💻 About the Developer

Hi! I'm **Mazen El-Gayar**, a **Senior Flutter Mobile Developer** from Egypt who decided to try something completely different: game development.

**Gambling Addiction** is my very first game—a small Unreal Engine project I built to learn game development and challenge myself outside of mobile apps. Every mechanic, blueprint, and bug fixed has been part of the learning journey.

Thank you for playing my first game. Your feedback and support genuinely mean a lot and will help shape my future projects.

---

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

You're stuck in a loop of risk. Magic balls litter the floor like chips on a table—heal when you can, roll orange and blue when you can't help yourself. The drones and the collapsing floors are the house edge.

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

### Strategy tips

- You **don't have to gamble**. You can survive by letting drones shoot each other or by baiting them onto collapsing floors instead of picking risky magic balls.
- Orange and blue spheres can help—or make your situation much worse. Decide whether the risk is worth it.
- Be careful when hiding behind the glass falling-floor cover. If one of your allies throws an **orange sphere**, it may spawn a new drone **inside your hiding spot**, trapping you with nowhere to escape.

### Death & possession

Drones fire blaster beams (`BP_BlasterBeam`). When your pawn dies, you **possess another living ally** if one remains. You're only fully out when the last pawn is gone.

### Falling floors

`BP_DroppingFloor` pieces start giving way at the **beginning of a round**—keep