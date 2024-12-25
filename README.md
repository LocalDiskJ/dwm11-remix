*Supports 22H2, 23H2, and 24H2. Insider Preview/Canary builds may not work.*

This mod allows the user to modify some parameters related to DWM windows. The default settings attempt
to recreate the Windows 7 style; additionally, the following is possible:

* Use Windows 8 positions and sizes
* Adjust the window radius curve
* Experiment with custom colorization/text color

There are also a few bonus options:

* The Mica titlebar effect can be activated and stretched down the entire window.
  * This can be told to use dark mode colors and/or Mica Light.
* Maximized windows can be darkened as seen in Windows Vista.
  * This option is subject to side effects from other programs hooking into DWM (i.e. OpenGlass/DWMBlurGlass).
* The titlebar text can be centered, for entertainment purposes only.

<details><summary><b>Screenshots</b> (click to expand)</summary>
  
>* Default configuration:
>  
>![image](/screenshots/config-default.png)
>* Default configuration with Windows 8 metrics:
>  
>![image](/screenshots/config-eight-mode.png)
>* Windows 8 metrics with Mica:
>  
>![image](/screenshots/config-eight-mica.png)
>* Windows 7 metrics with Mica type/Window state synchronization:
>  
>![image](/screenshots/config-seven-mica2.png)
>* Windows 8 metrics with centered titlebar text:
>  
>![image](/screenshots/config-eight-center.png)
</details>

## Installation
1. Open Windhawk's GUI and click on `Create a New Mod` (in bottom-right)
2. Copy the contents of `local@dwm11-remix.wh.cpp` into the editor, and then click `Compile Mod`

## Notes
* **`dwm.exe` needs to be present in the process inclusion list in Windhawk's advanced settings.**
  * The mod will silently fail to inject if the process is not listed.
* Depending on which metric style you want to use, adjust your titlebar height accordingly:
  * For Windows 7, titlebar height should be set to 21, and 17 for tool windows.
  * For Windows 8, titlebar height should be set to 22 for both normal and tool windows.
* This mod incorporates and expands upon elements from the following:
  * Bring Back the Borders! - teknixstuff
  * "[DWM thick frames test](https://github.com/Maplespe/DWMBlurGlass/issues/147#issuecomment-2052520952)" - Xdmg01
  * "Restore Seven/Eight Caption Buttons"/Aero Window Manager - Dulappy
