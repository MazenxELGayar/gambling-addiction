"""
Optional helper: after compiling NaughtyBot, you can call Show Game Over Screen
from Blueprints directly. Quit Game is already intercepted by NaughtyBotGameInstance
during gameplay, so Blueprint edits are not required for Game Over to appear.

If you prefer an explicit node instead of Quit Game:
  Game Flow -> Show Game Over Screen
"""

import unreal


def main():
    unreal.log("NaughtyBot: Quit Game during gameplay is intercepted -> Game Over screen.")
    unreal.log("Main menu map: Lvl_MainMenu | Gameplay map: NaughtMap")
    for path in (
        "/Game/BluePrints/Drone/BP_BlasterBeam",
        "/Game/BluePrints/Sphere/BP_SpawnAllySphere",
        "/Game/Maps/Lvl_MainMenu",
        "/Game/Maps/NaughtMap",
    ):
        exists = unreal.EditorAssetLibrary.does_asset_exist(path)
        unreal.log(f"  {'OK' if exists else 'MISSING'}: {path}")


if __name__ == "__main__":
    main()
