
# CogitatorOS - The Only Operating System You'll Ever Need

<!-- TODO: Add more features for more immersive interaction -->

CogitatorOS is an immersive, command-line-based operating system inspired by the Adeptus Mechanicus of Warhammer 40K. It brings an aesthetic of binary code, scrolling text, and protocol displays right to your terminal. With features designed to mimic the operation of ancient cogitators, it offers a retro-tech feel that blends the mechanical with the digital.

## Features

- **Adeptus Mechanicus-Like Boot-Up**: Display real-time system status updates in binary with dynamic transition animations.
- **Interactive Command Shortcuts**: Control your cogitator with simple key commands to scroll, pause, reset, or quit.
- **Binary Status Codes**: Show system success ("OK") or failure ("FAIL") in green or red, respectively.
- **Awaiting Input Mode**: Once online, CogitatorOS waits for your commands while giving you live feedback with binary status.

## Installation

```bash
1. Clone this repository:
   git clone https://github.com/Guakocius/CogitatorOS.git
   cd CogitatorOS

2. Install dependencies (ensure `ncurses` is available on your system):
   - For **Debian/Ubuntu**:
     sudo apt-get install libncurses5-dev gcc-multilib libc6-dev-i386

   - For **Arch Linux**:
     sudo pacman -S ncurses gcc-multilib

3. Build the project:
   make

4. Run CogitatorOS:
   qemu-system-i386 -drive format=raw,file=./boot/img/CogitatorOS.img

```

## Controls

- Arrow Keys: Scroll the text up or down.
- P: Pause/resume text display.
- R: Reset the text to the beginning.
- Q: Quit CogitatorOS.

## How It Works

CogitatorOS simulates an ancient system boot-up sequence. During startup, it shows the loading process in binary, transitions through various states of the machine spirit, and displays dynamic feedback on the cogitator’s health (OK/FAILURE) in real-time. The system waits for your input once it's online, allowing interaction through keyboard shortcuts.

<!-- TODO: Develop CogitatorOS enough to being able to include screenshots; ## Screenshots -->

## Contributing

CogitatorOS is an open-source project. If you'd like to contribute, please fork this repository and submit pull requests with your changes. Contributions are welcome for new features, bug fixes, and improving the existing codebase.

## Licence

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Adeptus Mechanicus (Warhammer 40K): Inspiration for the aesthetics and lore.
- ncurses: Library used to manage terminal-based interfaces.
- You: For using CogitatorOS!

## Future Plans

- Add more interactive features, like system diagnostics and machine prayers.
- Implement a graphical user interface (GUI) version, combining terminal and graphical elements for full immersion.
- Enhance animations and sound effects for a truly cogitator-like experience.

By following these updated instructions, users should be able to build and run the CogitatorOS project as it currently stands.

### Explanation of Changes

1. **Installation Instructions**:
   - Updated to include the installation of dependencies (`libncurses5-dev`, `gcc-multilib`, `libc6-dev-i386`).
   - Added instructions to build the project using `make`.

2. **Running the Project**:
   - Updated to include instructions for running the project using `qemu`.

3. **General Updates**:
   - Ensured the README reflects the current state of the project, including the use of the `Makefile`.
