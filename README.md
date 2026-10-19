# Our customized JPEGView

A lean, fast Windows image viewer customized for quick photo cropping for
iNaturalist uploads. Open a photo, press a number key to pick a crop shape,
drag a box, let go — cropped. `Ctrl+Up` saves instantly. That's the whole workflow.

**Tip: you can copy-paste this whole page into Claude and ask it to help you set
everything up — it has all the context Claude needs.**

## Installing it on your own computer

### Option A - Install the ready-made build (recommended, ~2 minutes)

No installer needed; JPEGView is fully portable.

1. Download `JPEGView-custom-x64.zip` from this repo's **Releases** page
   (or from wherever it was sent to you directly).
2. Unzip it to a permanent folder you like, for example `C:\Tools\JPEGView`.
   (Don't run it from inside the zip or from Downloads — pick a real home for it.)
3. Run `JPEGView.exe` from that folder.
   - If Windows SmartScreen shows "Windows protected your PC", click **More info → Run anyway**.
     That warning appears only because this is a home-built program without a paid code-signing certificate.
4. To make it the default viewer for images: right-click any `.jpg` → **Open with →
   Choose another app** → browse to `JPEGView.exe` → check **Always**.

That's it. The custom keyboard shortcuts and crop behavior are baked into the
`KeyMap.txt.default` and `JPEGView.ini` files in the folder — no extra configuration needed.

Requirements: 64-bit Windows 7 or later. If the program complains about missing
`VCRUNTIME140.dll`, install the Microsoft Visual C++ Redistributable (x64) from
https://aka.ms/vs/17/release/vc_redist.x64.exe and run it again.

### Option B - Build it from source yourself

Only needed if you want to modify the code or no zip is available.

1. Install **Visual Studio 2022 Community** (free) with the
   **"Desktop development with C++"** workload.
2. Clone this repository.
3. Open `src\JPEGView.sln` in Visual Studio 2022.
4. In the toolbar, set the configuration to **Release** and the platform to **x64**.
5. In Solution Explorer, right-click the **JPEGView** project → **Build**.
   - Do NOT use "Build Solution": the `JPEGView.Setup` installer project fails unless the
     WiX Toolset is installed. That error is expected and safe to ignore — you only need
     the JPEGView project itself.
6. The finished program is in `src\JPEGView\bin\x64\Release\` — run `JPEGView.exe` from
   there, or copy that whole folder somewhere permanent.
7. If the exe reports missing DLLs on startup (e.g. `libpng16.dll`, `lcms2-2.dll`), copy the
   named DLLs into the same folder as `JPEGView.exe`. (This happens if the machine that built
   it had vcpkg integration enabled; the shipped zip already includes them.)

## The custom crop workflow

| Key / action | What it does |
|---|---|
| drag with left mouse | select an area — **the crop happens the moment you release the button** |
| `1` | crop box locked to 1:1 square (what iNaturalist displays) |
| `2` / `3` / `4` | crop box locked to 4:3 / 3:2 / 16:9 |
| `5` | crop box locked to the image's own aspect ratio |
| `9` | crop box locked to an exact pixel size (a dialog asks for the size) |
| `0` | back to free-form cropping |
| hold `Shift` while dragging | force a square selection just this once |
| `Esc` while dragging | cancel the selection |
| `M` | crop the current selection (only needed if auto-crop is turned off) |

Other shortcuts: `Ctrl+Up` saves instantly without a prompt, `Ctrl+Shift+Up` opens the
save-as dialog, `X` sorts files by modification date.

A preset key (`1`, `2`, ...) sticks until you change it: press it once, then every crop
you draw keeps that shape. Cropping changes what's on screen; press `Ctrl+Up` or `Ctrl+S`
to actually save the file.

To turn off auto-crop-on-release and get the stock JPEGView behavior back, open
`JPEGView.ini` (next to the exe, or in `%APPDATA%\JPEGView\`) and set
`AutoCropOnMouseRelease=false`.

Everything else works like normal JPEGView: arrow keys to move between photos,
`+`/`-` to zoom, `F11` for fullscreen, `F1` for the built-in help.

## Credits

Based on [JPEGView](https://github.com/sylikc/jpegview) by sylikc, which continues the
original JPEGView by David Kleiner. Licensed under the GPL-2.0 (see LICENSE.txt).
