# Install Instructions

- [Dependencies](#dependencies)
- [Linux](#linux)
  - [Simple install](#simple-install)
    - [Arch](#arch-easy)
    - [Debian](#debian-easy)
    - [Fedora](#fedora-easy)
    - [Gentoo](#gentoo-easy)
    - [openSUSE](#opensuse-easy)
    - [Slackware](#slackware-easy)
    - [Ubuntu](#ubuntu-easy)
  - [Install git](#install-git)
    - [Arch](#arch-git)
    - [Debian](#debian-git)
    - [Fedora](#fedora-git)
    - [openSUSE](#opensuse-git)
    - [Ubuntu](#ubuntu-git)
  - [Clone qTox](#clone-qtox)
  - [GCC, Qt, FFmpeg, OpenAL Soft and qrencode](#other-deps)
    - [Arch](#arch-other-deps)
    - [Debian](#debian-other-deps)
    - [Fedora](#fedora-other-deps)
    - [openSUSE](#opensuse-other-deps)
    - [Slackware](#slackware-other-deps)
    - [Ubuntu](#ubuntu-other-deps)
  - [Compile dependencies](#compile-dependencies)
    - [docker](#docker)
    - [Compile toxcore](#compile-toxcore)
  - [Compile qTox](#compile-qtox)
  - [Security hardening with AppArmor](#security-hardening-with-apparmor)
- [BSD](#bsd)
  - [FreeBSD](#freebsd-easy)
- [macOS](#macos)
- [Windows](#windows)
  - [Cross-compile from Linux](#cross-compile-from-linux)
  - [Native](#native)
- [Compile-time switches](#compile-time-switches)

## Dependencies

| Name          | Version   | Modules                                          |
| ------------- | --------- | ------------------------------------------------ |
| [Qt]          | >= 6.2.0  | concurrent, core, gui, network, svg, widget, xml |
| [GCC]/[MinGW] | >= 11     | C++17 enabled                                    |
| [toxcore]     | >= 0.2.20 | core, av                                         |
| [FFmpeg]      | >= 2.6.0  | avformat, avdevice, avcodec, avutil, swscale     |
| [CMake]       | >= 3.10   |                                                  |
| [OpenAL Soft] | >= 1.16.0 |                                                  |
| [qrencode]    | >= 3.0.3  |                                                  |
| [sqlcipher]   | >= 3.2.0  |                                                  |
| [pkg-config]  | >= 0.28   |                                                  |

## Optional dependencies

They can be disabled/enabled by passing arguments to `cmake` command when
building qTox.

If they are missing, qTox is built without support for the functionality.

### Spell checking support

| Name     | Version |
| -------- | ------- |
| [sonnet] | >= 6.0  |

Use `-DSPELL_CHECK=OFF` to disable it.

**Note:** Specified version was tested and works well. You can try to use older
version, but in this case you may have some errors (including a complete lack
of spell check).

### Linux

#### Auto-away support

| Name            | Version  |
| --------------- | -------- |
| [libXScrnSaver] | >= 1.2   |
| [libX11]        | >= 1.6.0 |

Disabled if dependencies are missing during compilation.

## Linux

### Simple install

Easy qTox install is provided for variety of distributions:

- [Arch](#arch)
- [Debian](#debian)
- [Fedora](#fedora)
- [Gentoo](#gentoo)
- [Slackware](#slackware)
- [Ubuntu](#ubuntu)

---

<a name="arch-easy" />

#### Arch

PKGBUILD is available in the `community` repo, to install:

```bash
pacman -S qtox
```

<a name="debian-easy" />

#### Debian

qTox is available in the [Main](https://tracker.debian.org/pkg/qtox) repo, to install:

```bash
sudo apt install qtox
```

<a name="fedora-easy" />

#### Fedora

qTox is available in the [RPM Fusion](https://rpmfusion.org/) repo, to install:

```bash
dnf install qtox
```

<a name="gentoo-easy" />

#### Gentoo

qTox is available in Gentoo.

To install:

```bash
emerge qtox
```

<a name="opensuse-easy" />

#### openSUSE

qTox is available in openSUSE Factory.

To install in openSUSE 15.0 or newer:

```bash
zypper in qtox
```

To install in openSUSE 42.3:

```bash
zypper ar -f https://download.opensuse.org/repositories/server:/messaging/openSUSE_Leap_42.3 server:messaging
zypper in qtox
```

<a name="slackware-easy" />

#### Slackware

qTox SlackBuild and all of its dependencies can be found here:
http://slackbuilds.org/repository/14.2/network/qTox/

---

If your distribution is not listed, or you want / need to compile qTox, there
are provided instructions.

---

Most of the dependencies should be available through your package manager.

<a name="ubuntu-easy" />

#### Ubuntu

qTox is available in the [Universe](https://packages.ubuntu.com/focal/qtox) repo, to install:

```bash
sudo apt install qtox
```

### Install git

In order to clone the qTox repository you need Git.

<a name="arch-git" />

#### Arch Linux

```bash
sudo pacman -S --needed git
```

<a name="debian-git" />

#### Debian

```bash
sudo apt-get install git
```

<a name="fedora-git" />

#### Fedora

```bash
sudo dnf install git
```

<a name="opensuse-git" />

#### openSUSE

```bash
sudo zypper install git
```

<a name="ubuntu-git" />

#### Ubuntu

```bash
sudo apt-get install git
```

### Clone qTox

Afterwards open a new terminal, change to a directory of your choice and clone
the repository:

```bash
cd /home/$USER
git clone https://github.com/qTox/qTox.git qTox
cd qTox
```

The following steps assumes that you cloned the repository at
`/home/$USER/qTox`. If you decided to choose another location, replace
corresponding parts.

### Docker

Development can be done within one of the many provided docker containers. See the available configurations in docker-compose.yml. These docker images have all the required dependencies for development already installed. Run `docker compose run --rm ubuntu_lts` and proceed to [compiling qTox](#compile-qtox). If you want to avoid compiling as root in the docker image, you can run `USER_ID=$(id -u) GROUP_ID=$(id -g) docker compose run --rm ubuntu_lts` instead.

NOTE: qtox will not run in the docker container unless your x11 session allows connections from other users. If X11 is giving you issues in the docker image, try `xhost +` on your host machine

<a name="other-deps" />

### GCC, Qt, FFmpeg, OpenAL Soft and qrencode

<a name="arch-other-deps" />

Please see https://github.com/TokTok/dockerfiles/tree/master/qtox/docker for your distribution for an up to date list of commands to set up your build environment

### Compile dependencies

<a name="compile-toxcore" />

#### Compile toxcore

Provided that you have all required dependencies installed, you can simply run:

```bash
git clone https://github.com/TokTok/c-toxcore.git toxcore
cd toxcore
# Note: See https://github.com/TokTok/dockerfiles/blob/master/qtox/download/download_toxcore.sh
# for which version should be checked out.
cmake -B_build -H. -GNinja -DBOOTSTRAP_DAEMON=OFF
cmake --build _build
sudo cmake --install _build

# we don't know what whether user runs 64 or 32 bits, and on some distros
# (Fedora, openSUSE) lib/ doesn't link to lib64/, so add both
echo '/usr/local/lib64/' | sudo tee -a /etc/ld.so.conf.d/locallib.conf
echo '/usr/local/lib/' | sudo tee -a /etc/ld.so.conf.d/locallib.conf
sudo ldconfig
```

### Compile qTox

**Make sure that all the dependencies are installed.** If you experience
problems with compiling, it's most likely due to missing dependencies, so please
make sure that you did install _all of them_.

If you are compiling on Fedora 25, you must add libtoxcore to the
`PKG_CONFIG_PATH` environment variable manually:

```
# we don't know what whether user runs 64 or 32 bits, and on some distros
# (Fedora, openSUSE) lib/ doesn't link to lib64/, so add both
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/lib64/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig"
```

Run in qTox directory to compile:

```bash
cmake -B_build -H.
cmake --build _build
```

Now you can start compiled qTox with `_build/qtox`

Congratulations, you've compiled qTox `:)`

#### Debian / Ubuntu / Mint

If the compiling process stops with a missing dependency like:
`... libswscale/swscale.h missing` try:

```bash
apt-file search libswscale/swscale.h
```

And install the package that provides the missing file.
Start make again. Repeat if necessary until all dependencies are installed. If
you can, please note down all additional dependencies you had to install that
aren't listed here, and let us know what is missing `;)`

---

### Security hardening with AppArmor

See [AppArmor] to enable confinement for increased security.

## BSD

<a name="freebsd-easy" />

#### FreeBSD

qTox is available as a binary package. To install the qTox package:

```bash
pkg install qTox
```

The qTox port is also available at `net-im/qTox`. To build and install qTox
from sources using the port:

```bash
cd /usr/ports/net-im/qTox
make install clean
```

<a name="macos" />

## macOS

Supported macOS versions: >=10.15.

Compiling qTox on macOS for development requires 2 tools:
[Xcode](https://developer.apple.com/xcode/) and [homebrew](https://brew.sh).

### Manual Compiling

#### Required Libraries

Install homebrew if you don't have it:

```bash
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

First, clone qTox.

```bash
git clone https://github.com/qTox/qTox
cd qTox
```

Then install required dependencies available via `brew`.

```bash
brew bundle --file platform/macos/Brewfile
```

Then, install [toxcore](https://github.com/TokTok/c-toxcore/blob/master/INSTALL.md).

```bash
git clone --depth=1 https://github.com/TokTok/dockerfiles
dockerfiles/qtox/build_toxcore_system.sh
```

Finally, build qTox.

#### Compiling

```bash
cmake -B_build -H. -GNinja -DCMAKE_PREFIX_PATH=$(brew --prefix qt@6)
cmake --build _build
cmake --install _build
```

#### Running qTox

`qTox.dmg` should be in your `_build` directory. You can install qTox from the dmg
to your Applications folder, or run qTox directly from the dmg.

<a name="windows" />

## Windows

Only cross-compiling from Linux is supported and tested in CI, but building
under MSYS should also work.

### Cross-compile from Linux

See [`platform/windows/cross-compile`](platform/windows/cross-compile).

## Compile-time switches

They are passed as an argument to `cmake` command. E.g. with a switch `SWITCH`
that has value `ON` it would be passed to `cmake` in a following manner:

```bash
cmake -DSWITCH=ON
```

Look at the beginning of `CMakeLists.txt` for a list of options. Options that
are `ON` by default can be turned off by passing `-DSWITCH=OFF`.

[AppArmor]: /security/apparmor/README.md
[Atk]: https://wiki.gnome.org/Accessibility
[Cairo]: https://www.cairographics.org/
[Check]: https://libcheck.github.io/check/
[CMake]: https://cmake.org/
[DBus Menu]: https://launchpad.net/libdbusmenu
[FFmpeg]: https://www.ffmpeg.org/
[GCC]: https://gcc.gnu.org/
[libX11]: https://www.x.org/wiki/
[libXScrnSaver]: https://www.x.org/wiki/Releases/ModuleVersions/
[MinGW]: http://www.mingw.org/
[OpenAL Soft]: http://kcat.strangesoft.net/openal.html
[Pango]: http://www.pango.org/
[pkg-config]: https://www.freedesktop.org/wiki/Software/pkg-config/
[qrencode]: https://fukuchi.org/works/qrencode/
[Qt]: https://www.qt.io/
[toxcore]: https://github.com/TokTok/c-toxcore/
[sonnet]: https://github.com/KDE/sonnet
[libnotify]: https://gitlab.gnome.org/GNOME/libnotify
[sqlcipher]: https://github.com/sqlcipher/sqlcipher
