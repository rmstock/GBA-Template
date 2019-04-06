# GBA-Template

A GBA game project template written in C. Has moving background, sprites, music, and power saving.

## Getting Started

Install [**devkitARM**](http://devkitpro.org/wiki/Getting_Started/devkitARM) to the default directory (C:/devkitpro).
- make sure to install GBA Development and GP32 components.

Install [[**FFmpeg**]](https://ffmpeg.org/download.html).

Then download [**Cygwin**](http://cygwin.com/install.html): **setup-x86_64.exe** for 64-bit Windows, **setup-x86.exe** for 32-bit.

Run the Cygwin setup and leave the default settings. At "Select Packages", set the view to "Full" and choose to install the following:

- `make`
- `git`
- `gcc-core`
- `gcc-g++`
- `libpng-devel`

In the **Cygwin terminal**, enter these commands:

	export DEVKITPRO=/cygdrive/c/devkitpro
	echo export DEVKITPRO=$DEVKITPRO >> ~/.bashrc
	export DEVKITARM=$DEVKITPRO/devkitARM
	echo export DEVKITARM=$DEVKITARM >> ~/.bashrc

	git clone https://github.com/rmstock/GBA-Template
	cd GBA-Template
	make

Install a GBA emulator of your choice on a target system, or flash to a cart if you have one.

Run the game!



## Contributing

Please send a pull request to add features, I am looking for any improvements that help the game, build process, or documentation. It is very much a work in progress.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

See [Credits.txt](Credits.txt) for acknowledgments.
