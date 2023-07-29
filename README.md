# wattson-sdk
Minecraft 1.8.9 and 1.9.4 internal cheat

This will be a cheat I will update and give a free cheat to people who can't afford those premium cheats!

Join the official Discord server to keep up-to-date on this cheat: https://discord.gg/cD4CFYrMzJ

# How To Build
To build you will need to use [vcpkg](https://vcpkg.io/en/getting-started)

Once you have installed vcpkg you will need to run the vcpkg Visual Studio integration, using the following

`vcpkg integrate install`

Once you have integrated vcpkg into Visual Studio you will need these packages in order to build the project.

`vcpkg install imgui:x64-windows-static-md`

`vcpkg install imgui[freetype]:x64-windows-static-md`

`vcpkg install imgui[opengl2-binding]:x64-windows-static-md`

`vcpkg install imgui[win32-binding]:x64-windows-static-md`

`vcpkg install minhook:x64-windows-static-md`

After every package has been installed correctly, restart your system and open the wattson-sdk project.

If you're unable to build, make sure your vcpkg triplet is `x64-windows-static-md` [example image](https://imgur.com/a81Faq2)

# SDK Features
- Version mapper
- Easy feature implementation
- OOP GUI framework
- Dear ImGui

# Cheat Features
- Name ESP
- Snapline ESP
- (1.9.4) Glow ESP
- Fullbright
