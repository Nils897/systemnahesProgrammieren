# Systemnahes Programmierung 2 - Projektabgabe

- Projekt für die Vorlesung Systemnahes Programmieren 2 in der 4. Theoriephase
- Contributor: Justin Lotwin, Linus Gerlach, Janne Nußbaum, Nils Fleschhut
- (Basisprojekt gegeben von Herrn Thomas Vogt)

## 1. Build zum laufen kriegen

## Arm Documentation
 - [Cortex M0 Startseite](https://developer.arm.com/Processors/Cortex-M0)
   - [Armv6-M Architecture Reference Manual](https://developer.arm.com/documentation/ddi0419/latest/)
   - [Arm Cortex-M0 Processor Datasheet](https://developer.arm.com/documentation/102834/0100/?lang=en)
   - [Cortex-M0 Devices Generic User Guide](https://developer.arm.com/documentation/dui0497/a/?lang=en)
   - [Cortex-M0 Technical Reference Manual r0p0](https://developer.arm.com/documentation/ddi0432/c/?lang=en)
 - [Arm Application Binary Interface](https://github.com/ARM-software/abi-aa)
 - [GNU Assembler Documentation](https://sourceware.org/binutils/docs-2.40/as/index.html)
 - [GNU Linker Documentation](https://sourceware.org/binutils/docs-2.40/ld/index.html)

## Simuliertes Board Info
 - [Nordic nRF boards (microbit)](https://www.qemu.org/docs/master/system/arm/nrf.html)
 - [Nordic nRF51822](https://www.nordicsemi.com/products/nrf51822)
 - [nRF51822 Product Specification v3.4](https://infocenter.nordicsemi.com/pdf/nRF51822_PS_v3.4.pdf)

## Prerequisites
 - Arm Cross Compiler Paket: _gcc-arm-none-eabi_
 - QEMU Arm Paket: _qemu-system-arm_
 - GDB (Multi-Arch) Paket: _gdb-multiarch_
 - CMake

Hinweis:
Unteranderem bei SUSE, Arch, NixOs scheint der standard GDB ein GDB-Multiarch zu sein.

### Windows
Installation von CMake über Download des Installers (https://cmake.org/download/)
oder Paketmanager `winget install CMake.CMake`.

Installation der ARM GCC Toolchain [Website](https://gnutoolchains.com/arm-eabi/)
Nach z.B. C:\Toolchains\
**WICHTIG:** zu PATH hinzufügen (lassen)

### Linux
Über Paketmanager Installieren:

**Ubuntu/ Debian**: ```sudo apt install gcc-arm-none-eabi cmake```

**Arch**:
```
yay -S gcc-arm-none-eabi-bin 
sudo pacman -S cmake
```

### macOS
```brew install gcc-arm-embedded```

## Building
Auschecken des Quellcodes:
`git clone https://github.com/infohoschie/arm-cortex-m0-cmake-start.git`

Erstellen des Build Mittels CMake Presets:
```cmake --preset arm-cortex-m0-unix```
oder
```cmake --preset arm-cortex-m0-mingw```

Bauen Mittels CMake Presets:
```cmake --build --preset arm-cortex-m0-unix```
oder
```cmake --build --preset arm-cortex-m0-mingw```

## Generiertes Output analysieren (optional)
 - ELF-Sections anzeige:
   `arm-none-eabi-objdump -x build-cortex-m0/testApp.elf`
 - ELF-File disassemblieren (mit Quellcode-Verknüpfung):
   `arm-none-eabi-objdump -d build-cortex-m0/testApp.elf`
   `arm-none-eabi-objdump -d -S build-cortex-m0/testApp.elf`

## QEMU Emulator starten und mit GDB verbinden
QEMU und GDB müssen in unterschiedlichen Konsolen (Shells) gestartet werden.
### - QEMU Emulation Starten:
   `qemu-system-arm -M microbit -device loader,file=build-cortex-m0/testApp.elf -nographic -S -s -serial mon:stdio`
### - GDB zu QEMU verbinden:
   `gdb-multiarch build-cortex-m0/testApp.elf -ex "target extended-remote localhost:1234" -ex "load"`
#### MacOS on Apple Silicon: 
   `arm-none-eabi-gdb build-cortex-m0/testApp.elf -ex "target extended-remote localhost:1234" -ex "load"`

Um QEMU zu beenden die Tastenkombination `<strg> + a` und anschließend `x` nutzen.

## IDEs
### Jetbrains CLion
Das Projekt kann direkt in der IDE geöffnet (ausgecheckt) werden.
Die CMake Presets werden direkt als build-target angeboten

Der integrierte Debugger kann direkt genutzt werden.
Unter der Run-Configuration kann der QEMU Aufruf als "Native Application" hinzugefügt werden.
Unter debug Configuration kann eine "Remote Debug" Konfiguration angelegt werden, bei der unter "target remote args" die Verbindungsdetails angeben und als *symbol file* die *testApp.elf* referenziert werden kann.

### Visual Studio Code

VS-Code kann über einen Workspace konfiguriert werden, welcher über die Datei "linux.code-workspace" bzw "windows.code-workspace" geöffnet werden kann.

Folgende Extensions werden benötigt:
- jkearins.action-buttons-ext
- webfreak.debug
- ms-vscode.cmake-tools
- dan-c-underwood.arm

Diese sind ebenfalls als empfohlene Extensions im Workspace definiert.

Nach Installation erkennt VScode die CMake Presets und bietet diese gleich an.
Ebenfalls werden in der Statusleiste Knöpfe um das CMake Projekt zu *konfigurieren* und zu *bauen*,
die qemu-Instanz (neu) zu *starten* und gdb zu starten hinzugefügt.

Nach Änderungen am Code muss das CMake Projekt neugebaut und die qemu-Instanz neugestartet werden.

## 2. Projekt

### Starten des Spiels
Da das Spiel mit User Input funkioniert, muss man das Projekt in der Shell starten. Am einfachsten ist es ein kleines "runHangman-Skript" zu machen. Befolgen sie hierzu folgende Schritte:
1. Gehen Sie mit cd in das directory in dem sie das Skript haben wollen
2. Erstellen der Datei mit: `touch runHangman`
3. Bearbeiten der Datei mit: `vi runHangman` (oder vim oder nano etc.)
4. In der Datei schreiben sie einfach untereinander folgendes:

   `cd Path/to/your/build/directory`

   `cmake --build --preset arm-cortex-m0-unix` bzw. `cmake --build --preset arm-cortex-m0-mingw`
