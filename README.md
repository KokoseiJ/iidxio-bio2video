# iidxio-bio2video
Implementation of Bemanitools iidxio API for BI2X IO boards.

## How do I use it?

### bi2xtest

Run the program, and the program will detect BI2X the same way a stock game would.
You can then review the outputs from BI2X and verify the inputs.

### iidxio-bi2x.dll

Place `libacc.dll`, `libaio.dll`, `libaio-iob.dll` and `libaio-iob2_video.dll` along with `iidxio-bi2x.dll`.
Rename `iidxio-bi2x.dll` to `iidxio.dll` and use it in place of Bemanitools-supplied `iidxio.dll`. No config is required for basic usage. However, `bio2video.ini` needs to be in the same directory as `iidxio-bi2x.dll` to customize RGB lights. Otherwise, the RGB LEDs will default to white.

Only the dlls from 27 HEROIC VERSE are tested, but newer dlls should work as well.

### RGB LED Settings
To customize the LED colours, change the hex colourcodes in `bio2video.ini`:

``` bio2video.ini
[LED]
Woofer=0xFF00FF
TTP1=0xFF0000
TTP2=0x0000FF
IccrP1=0xFF0000
IccrP2=0x0000FF
Pillar=0xFFFFFF
```

## Nerd section
### How do I build it?
Supply the aforementioned DLL files to `extern/dlls` folder, and build using CMake on Mingw64.

You are more than welcome to take the matter to your own hands and contribute back!

