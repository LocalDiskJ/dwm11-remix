// ==WindhawkMod==
// @id              dwm11-remix
// @name            DWM11 Remix
// @description     The best mod ever that does legendary things
// @version         1.0
// @include         dwm.exe
// @architecture    x86-64
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
*Supports 22H2, 23H2, and 24H2. Insider Preview/Canary builds may not work.*

This mod allows the user to tweak various aspects of DWM to their liking.
The default settings attempt to replicate the Windows 7 style; however,
the following customization options exist:

* Windows 8 metrics
* Window radius adjustment
* Colorization color / text color tweaks
* Shadow parameter modification

There are also a few bonus options:

* The Mica titlebar effect can be activated and stretched down the entire window.
  * This can be told to use dark mode colors and/or Mica Light.
* Maximized windows can be darkened as seen in Windows Vista.
  * This option is subject to side effects from other programs hooking into DWM (i.e. OpenGlass/DWMBlurGlass).
* An option exists to center the titlebar text, provided for entertainment purposes only.

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
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- eightMode: false
  $name: Windows 8 Mode
- centerText: false
  $name: Center Titlebar Text
  $description: This is only guaranteed to work with the default ASCII characters
- windowRadius: 76
  $name: Window Radius
  $description: This value gets divided by 10
- vistaBlackMax: false
  $name: Windows Vista Logic
  $description: When a window is maximized, it will become darkened and opaque, with white text
- totalAlpha: 80
  $name: Window Background Opacity %
- textColor: true
  $name: Enable Custom Text Color
- textColorValues:
  - R: 0
  - G: 0
  - B: 0
  $name: Custom Text Color Values
- textColor2: true
  $name: Enable Custom Inactive Text Color
- textColor2Values:
  - R: 0
  - G: 0
  - B: 0
  $name: Custom Inactive Text Color Values
- colorScience: false
  $name: Enable Custom Colorization Color
- colorScienceValues: 
  - R: 116
  - G: 184
  - B: 252
  - A: 196
  $name: Custom Colorization Color Values
- colorScience2: false
  $name: Enable Custom Inactive Background Color
- colorScience2Values: 
  - R: 222
  - G: 238
  - B: 254
  - A: 255
  $name: Custom Inactive Background Color Values
- micaMode: false
  $name: Mica Mode
  $description: Activate the Mica titlebar effect and extend it down the entire window
- darkMode: false
  $name: Dark Mode
  $description: Toggle dark mode colors on the Mica backdrop
- micaRich: false
  $name: Use Mica Light
  $description: A more "vibrant" type of Mica
- micaSync: false
  $name: Sync Mica Type with Window State
  $description: Active windows use Mica Light, inactive windows use normal Mica
- disableShadows: false
  $name: Disable Shadows
- category1:
  - sqSize1: 16
    $name: Shadow Area Size
  - shadowOpacityWeird1: 14
    $name: Shadow 1 Opacity
  $name: Context Menu Shadows
  $description: The opacity values get divided by 100
- category2:
  - sqSize2: 25
    $name: Shadow Area Size
  - stretchSize2: 20
    $name: Shadow Stretch Size
  - shadowOpacityWeird2: 0
    $name: Shadow 1 Opacity
  - shadowOpacity2: 150
    $name: Shadow 2 Opacity
  $name: Active Window Shadows
  $description: The opacity values get divided by 100
- category3:
  - sqSize3: 25
    $name: Shadow Area Size
  - stretchSize3: 20
    $name: Shadow Stretch Size
  - shadowOpacityWeird3: 0
    $name: Shadow 1 Opacity
  - shadowOpacity3: 75
    $name: Shadow 2 Opacity
  $name: Inactive Window Shadows
  $description: The opacity values get divided by 100
- category4:
  - sqSize4: 64
    $name: Shadow Area Size
  - stretchSize4: 43
    $name: Shadow Stretch Size
  - shadowOpacityWeird4: 56
    $name: Shadow 1 Opacity
  - shadowOpacity4: 55
    $name: Shadow 2 Opacity
  $name: Category 4 Shadows
  $description: This seems to be used by the modern UAC/Security dialogs
*/
// ==/WindhawkModSettings==

#include <windhawk_api.h>
#include <windhawk_utils.h>
#include <cwchar>
struct {
    bool eightMode;
    bool centerText;
    int windowRadius;
    bool vistaBlackMax;
    float totalAlpha;
    bool textColor;
    int textColorR;
    int textColorG;
    int textColorB;
    bool textColor2;
    int textColorR2;
    int textColorG2;
    int textColorB2;
    bool colorScience;
    int red1;
    int green1;
    int blue1;
    int alpha1;
    bool colorScience2;
    int red2;
    int green2;
    int blue2;
    int alpha2;
    bool micaMode;
    bool darkMode;
    bool micaRich;
    bool micaSync;
    bool disableShadows;
    float sqSize1;
    float shadowOpacityWeird1;
    float sqSize2;
    float stretchSize2;
    float shadowOpacityWeird2;
    float shadowOpacity2;
    float sqSize3;
    float stretchSize3;
    float shadowOpacityWeird3;
    float shadowOpacity3;
    float sqSize4;
    float stretchSize4;
    float shadowOpacityWeird4;
    float shadowOpacity4;
} settings;
void LoadSettings() {
    settings.eightMode = Wh_GetIntSetting(L"eightMode");
    settings.centerText = Wh_GetIntSetting(L"centerText");
    settings.windowRadius = Wh_GetIntSetting(L"windowRadius");
    settings.vistaBlackMax = Wh_GetIntSetting(L"vistaBlackMax");
    settings.totalAlpha = Wh_GetIntSetting(L"totalAlpha");
    settings.textColor = Wh_GetIntSetting(L"textColor");
    settings.textColorR = Wh_GetIntSetting(L"textColorValues.R");
    settings.textColorG = Wh_GetIntSetting(L"textColorValues.G");
    settings.textColorB = Wh_GetIntSetting(L"textColorValues.B");
    settings.textColor2 = Wh_GetIntSetting(L"textColor2");
    settings.textColorR2 = Wh_GetIntSetting(L"textColor2Values.R");
    settings.textColorG2 = Wh_GetIntSetting(L"textColor2Values.G");
    settings.textColorB2 = Wh_GetIntSetting(L"textColor2Values.B");
    settings.colorScience = Wh_GetIntSetting(L"colorScience");
    settings.red1 = Wh_GetIntSetting(L"colorScienceValues.R");
    settings.green1 = Wh_GetIntSetting(L"colorScienceValues.G");
    settings.blue1 = Wh_GetIntSetting(L"colorScienceValues.B");
    settings.alpha1 = Wh_GetIntSetting(L"colorScienceValues.A");
    settings.colorScience2 = Wh_GetIntSetting(L"colorScience2");
    settings.red2 = Wh_GetIntSetting(L"colorScience2Values.R");
    settings.green2 = Wh_GetIntSetting(L"colorScience2Values.G");
    settings.blue2 = Wh_GetIntSetting(L"colorScience2Values.B");
    settings.alpha2 = Wh_GetIntSetting(L"colorScience2Values.A");
    settings.micaMode = Wh_GetIntSetting(L"micaMode");
    settings.darkMode = Wh_GetIntSetting(L"darkMode");
    settings.micaRich = Wh_GetIntSetting(L"micaRich");
    settings.micaSync = Wh_GetIntSetting(L"micaSync");
    settings.disableShadows = Wh_GetIntSetting(L"disableShadows");
    settings.sqSize1 = Wh_GetIntSetting(L"category1.sqSize1");
    settings.shadowOpacityWeird1 = Wh_GetIntSetting(L"category1.shadowOpacityWeird1");
    settings.sqSize2 = Wh_GetIntSetting(L"category2.sqSize2");
    settings.stretchSize2 = Wh_GetIntSetting(L"category2.stretchSize2");
    settings.shadowOpacityWeird2 = Wh_GetIntSetting(L"category2.shadowOpacityWeird2");
    settings.shadowOpacity2 = Wh_GetIntSetting(L"category2.shadowOpacity2");
    settings.sqSize3 = Wh_GetIntSetting(L"category3.sqSize3");
    settings.stretchSize3 = Wh_GetIntSetting(L"category3.stretchSize3");
    settings.shadowOpacityWeird3 = Wh_GetIntSetting(L"category3.shadowOpacityWeird3");
    settings.shadowOpacity3 = Wh_GetIntSetting(L"category3.shadowOpacity3");
    settings.sqSize4 = Wh_GetIntSetting(L"category4.sqSize4");
    settings.stretchSize4 = Wh_GetIntSetting(L"category4.stretchSize4");
    settings.shadowOpacityWeird4 = Wh_GetIntSetting(L"category4.shadowOpacityWeird4");
    settings.shadowOpacity4 = Wh_GetIntSetting(L"category4.shadowOpacity4");
}
typedef struct _MARGINS {
  int cxLeftWidth;
  int cxRightWidth;
  int cyTopHeight;
  int cyBottomHeight;
} MARGINS,*PMARGINS;
typedef struct _D3DCOLORVALUE {
    float r;
    float g;
    float b;
    float a;
} D3DCOLORVALUE;
union GpCC {
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE a;
	};
	UINT32 argb;
};
// code region: center text algorithm
struct textWidthMap {
    char letter;
    float width;
};
textWidthMap twMap[] = { //approximate char width for 9pt Segoe UI at 96 dpi
        {0, 0},       {1, 0},      {2, 0},      {3, 0},      {4, 0},       {5, 0},       {6, 0},      {7, 0},
        {8, 0},       {9, 0},      {10, 0},     {11, 0},     {12, 0},      {13, 0},      {14, 0},     {15, 0},
        {16, 0},      {17, 0},     {18, 0},     {19, 0},     {20, 0},      {21, 0},      {22, 0},     {23, 0},
        {24, 0},      {25, 0},     {26, 0},     {27, 0},     {28, 0},      {29, 0},      {30, 0},     {31, 0},
        {' ', 3.28},  {'!', 3.40}, {'"', 4.70}, {'#', 7.10}, {'$', 6.47},  {'%', 9.82},  {'&', 9.60}, {'\'', 2.75},
        {'(', 3.62},  {')', 3.62}, {'*', 5.00}, {'+', 8.20}, {',', 2.60},  {'-', 4.80},  {'.', 2.60}, {'/', 4.70},
        {'0', 6.47},  {'1', 6.44}, {'2', 6.47}, {'3', 6.47}, {'4', 6.47},  {'5', 6.47},  {'6', 6.47}, {'7', 6.47},
        {'8', 6.47},  {'9', 6.47}, {':', 2.60}, {';', 2.60}, {'<', 8.20},  {'=', 8.20},  {'>', 8.20}, {'?', 5.38},
        {'@', 11.45}, {'A', 7.74}, {'B', 6.88}, {'C', 7.12}, {'D', 8.40},  {'E', 6.06},  {'F', 5.86}, {'G', 8.24},
        {'H', 8.52},  {'I', 3.20}, {'J', 3.82}, {'K', 6.96}, {'L', 5.65},  {'M', 10.77}, {'N', 9.97}, {'O', 9.06},
        {'P', 7.72},  {'Q', 9.06}, {'R', 7.18}, {'S', 6.37}, {'T', 6.52},  {'U', 8.24},  {'V', 7.45}, {'W', 11.21},
        {'X', 7.08},  {'Y', 6.64}, {'Z', 6.84}, {'[', 3.62}, {'\\', 4.56}, {']', 3.62},  {'^', 8.20}, {'_', 4.98},
        {'`', 3.22},  {'a', 6.10}, {'b', 7.05}, {'c', 5.55}, {'d', 7.05},  {'e', 6.30},  {'f', 3.80}, {'g', 7.05},
        {'h', 6.80},  {'i', 2.90}, {'j', 2.95}, {'k', 6.00}, {'l', 2.90},  {'m', 10.3},  {'n', 6.80}, {'o', 7.05},
        {'p', 7.05},  {'q', 7.05}, {'r', 4.20}, {'s', 5.10}, {'t', 4.10},  {'u', 6.80},  {'v', 5.75}, {'w', 8.70},
        {'x', 5.50},  {'y', 5.80}, {'z', 5.45}, {'{', 3.62}, {'|', 2.87},  {'}', 3.62},  {'~', 8.20}, {127, 0}
};
wchar_t stringCache[256] = {};
int widthCache = 0;
int CalculateTextWidth(wchar_t* string, int charCount) {
    if (wcscmp(stringCache, string) == 0) {
        Wh_Log(L"   [x] no this is duplicate");
        return widthCache;
    }
    int index = 0;
    float width = 0;
    for (index = 0; index < charCount; index++) {
        //Wh_Log(L"the char [%c]", string[index]);
        if (string[index] > 127) {
            Wh_Log(L"[!] unexpected char [%i] at position %i", string[index], index);
            width += 5.0;
        }
        else width += twMap[string[index]].width;
    }
    int strWidth = ceil(width) + 2;
    Wh_Log(L"   [i] string length is %i", strWidth);
    wcscpy(stringCache, string);
    widthCache = strWidth;
    return strWidth;
}
//certain window classes cause issues with DWM for some reason.
//if we find one, pretend like the center text option is off
bool IsWindowClassValid(wchar_t* windowClass) {
    if (wcscmp(windowClass, L"") == 0) return false;
    if (wcscmp(windowClass, L"Ghost") == 0) return false; //the "(Not Responding)" overlays cause a softlock, so we have to exclude them
    if (wcscmp(windowClass, L"gdkWindowTemp") == 0) return false; //FindWindow() picks up this instead of "gdkWindowToplevel"
    return true;
}
// code region: structs
int pmoVisualMargins = 136;
int pmoVisualSize = 128;
struct CVisual {
    MARGINS insetMargins() {
        return *(MARGINS*)(this + pmoVisualMargins);
    }
    void editInsetMargins(MARGINS newMarginData) {
        *(MARGINS*)(this + pmoVisualMargins) = newMarginData;
    }
    SIZE visualSize() {
        return *(SIZE*)(this + pmoVisualSize);
    }
    void editVisualSize(SIZE newSizeData) {
        *(SIZE*)(this + pmoVisualSize) = newSizeData;
    }
};
struct CWindowData {
    DWORD windowStyle() {
        return *(long*)(this + 116);
    }
    DWORD windowStyleEx() {
        return *(long*)(this + 120);
    }
    MARGINS frameMargins() {
        return *(MARGINS*)(this + 64);
    }
    RECT windowCoordinates() {
        return *(RECT*)(this + 48);
    }
    SIZE windowSize() {
        RECT windowCords = *(RECT*)(this + 48);
        SIZE size = {};
        size.cx = windowCords.right - windowCords.left;
        size.cy = windowCords.bottom - windowCords.top;
        return size;
    }
    int dpiValue() {
        return *(int*)(this + 348);
    }
    HWND hWnd() {
        return *((HWND*)this + 5);
    }
    int accentPolicy() {
        return *(int*)(this + 168);
    }
    bool isAccentPolicyActive(int policy) {
        if (policy == 0 ||  policy == 5 || policy == 6) return false;
        else return true;
    }
    bool hasIcon() {
        return *(int *)(this + 152);
    }
    int backgroundType() {
        return *(int*)(this + 204);
    }
    void setBackgroundType(int type) {
        *(int*)(this + 204) = type;
    }
    bool isDarkMode() {
        return (*(byte*)(this + 0x2a5) >> 2 & 1);
    }
    void setDarkMode(bool mode) {
        *(byte*)(this + 0x2a5) = ((*(byte*)(this + 0x2a5) & 0xfb) | mode << 2);
    }
};
int pmoWindowData = 752;
int pmoSystemBackdrop = 320;
int pmoSystemBackdropType = 840;
int pmoState1 = 248;
int pmoState2 = 624;
int pmoClientMargins = 628;
int pmoBorderMargins = 660;
int pmoBorderMarginsMax = 676;
int pmoClientTest = 520;
int pmoClientVisual = 592;
int pmoButtonVisual = 528;
int pmoIconVisual = 576;
int pmoTextVisual = 560;
int pmoUnknownVisual = 336;
bool (*TreatAsActiveWindow)(byte* window);
struct CTopLevelWindow {
    CWindowData* windowData() {
        return (CWindowData*)*(long long *)(this + pmoWindowData);
    }
    bool isWindow() {
        return *(int *)((byte *)this + pmoState2) & 6;
    }
    bool isMaximized() {
        return *(int *)((byte *)this + pmoState1) & 4;
    }
    bool isTool() {
        return *(int *)((byte *)this + pmoState2) & 2;
    }
    bool isActive() {
        return TreatAsActiveWindow((byte*)this);
    }
    CVisual* systemBackdrop() {
        return (CVisual*)*(long long *)(this + pmoSystemBackdrop);
    }
    int systemBackdropType() {
        return *(int *)(this + pmoSystemBackdropType);
    }
    MARGINS clientMargins() {
        return *(MARGINS*)(this + pmoClientMargins);
    }
    MARGINS* borderMargins() {
        return (MARGINS*)(this + pmoBorderMargins);
    }
    MARGINS* borderMarginsMax() {
        return (MARGINS*)(this + pmoBorderMarginsMax);
    }
    CVisual* butttonVisual(int buttonType) {
        return (CVisual*)*(long long *)((this + pmoButtonVisual) + (buttonType * 8));
    }
    bool isSoloClose() {
        return !(*(int *)((byte *)this + pmoState2) & 2816);
    }
    CVisual* iconVisual() {
        return (CVisual*)*(long long *)(this + pmoIconVisual);
    }
    CVisual* textVisual() {
        return (CVisual*)*(long long *)(this + pmoTextVisual);
    }
    CVisual* clientVisual() {
        return (CVisual*)*(long long *)(this + pmoClientVisual);
    }
    bool clientTest() {
        return *(long long *)(this + pmoClientTest);
    }
    CVisual* unknownVisual() {
        return (CVisual*)*(long long *)(this + pmoUnknownVisual);
    }
    bool iconTest() {
        return *(int *)((byte *)this + pmoState2) & 0x10000;
    }
};
// code region: window metrics
void (*SetDirtyFlags)(CVisual* visual, unsigned long p1);
void UpdateNCButton(CTopLevelWindow* window, int buttonType, int insetTop, int* insetRight, int dpiValue) {
    CVisual* buttonVisual = window->butttonVisual(buttonType);
    if (!buttonVisual) return;

    MARGINS buttonInsets = buttonVisual->insetMargins();
    SIZE buttonSize = buttonVisual->visualSize();
    float widthCloseSolo = 2.333333;
    float widthClose = 2.333333;
    float widthMid = 1.285714;
    float widthEnd = 1.380952;
    if (settings.eightMode) {
        widthCloseSolo = 1.636364;
        widthClose = 2.227273;
        widthMid = 1.227273;
        widthEnd = 1.318182;
    }
    if (!window->isTool()) {
        buttonSize.cy = GetSystemMetricsForDpi((int)31, (UINT)dpiValue);
        if (settings.eightMode) buttonSize.cy -= 1;
        if (buttonType == 3) { // close
            if (window->isSoloClose()) {
                buttonSize.cx = floor((buttonSize.cy * widthCloseSolo) + 0.5);
            }
            else {
                buttonSize.cx = floor((buttonSize.cy * widthClose) + 0.5);
            }
        }
        else if (buttonType == 2) { // maximize/restore
            buttonSize.cx = floor((buttonSize.cy * widthMid) + 0.5);
        }
        else if (buttonType == 1 || buttonType == 0) { // minimize/help
            buttonSize.cx = floor((buttonSize.cy * widthEnd) + 0.5);
        }
        buttonSize.cy -= 1;
        buttonInsets.cyTopHeight = insetTop;
        buttonInsets.cxRightWidth = *insetRight;
        if (settings.eightMode && window->isMaximized()) buttonInsets.cyTopHeight += 1;
    }
    else {
        MARGINS toolFrameMargins = window->clientMargins();
        buttonSize.cy = GetSystemMetricsForDpi((int)53, (UINT)dpiValue) - 1;
        if (!settings.eightMode) buttonSize.cy += 1;
        buttonSize.cx = buttonSize.cy;
        buttonInsets.cxRightWidth = *insetRight;
        if (settings.eightMode) buttonInsets.cxRightWidth += 2;
        buttonInsets.cyTopHeight = toolFrameMargins.cyTopHeight - buttonSize.cy - 4;
        if (settings.eightMode) buttonInsets.cyTopHeight -= 1;
    }
    buttonVisual->editVisualSize(buttonSize);
    buttonVisual->editInsetMargins(buttonInsets);
    SetDirtyFlags(buttonVisual, 2);
    *insetRight += buttonSize.cx;
    return;
}
int textWidth = 0;
long (*UpdatePinnedParts)(CTopLevelWindow* window);
//for convenience when looking at logs, UpdateNCAreaPositionsAndSizes
//was shortened to just UpdateNCArea
long (*UpdateNCArea)(CTopLevelWindow* window);
long UpdateNCArea_H(CTopLevelWindow *window) {
    CWindowData* windowData = window->windowData();
    int dpiValue = windowData->dpiValue();
    MARGINS clientMargins = window->clientMargins();

    CVisual* clientVisual = window->clientVisual();
    if (window->clientTest()) {
        clientVisual->editInsetMargins(clientMargins);
        SetDirtyFlags(clientVisual, 2);
        CVisual* unknownVisual = window->unknownVisual();
        if (unknownVisual) unknownVisual->editInsetMargins(clientMargins);
    }
    MARGINS* borderSizes;
    int insetLeft = clientMargins.cxLeftWidth;
    int insetRight = clientMargins.cxRightWidth;
    int insetTop;
    if (window->isMaximized()) {
        borderSizes = window->borderMarginsMax();
        insetRight += 2;
        insetTop = borderSizes->cyTopHeight - 1;
    }
    else {
        borderSizes = window->borderMargins();
        insetRight -= 2;
        insetTop = borderSizes->cyTopHeight + 1;
    }
    
    for (int buttonType = 3; buttonType >= 0; buttonType--) 
        UpdateNCButton(window, buttonType, insetTop, &insetRight,  dpiValue);
    
    if (settings.eightMode) insetLeft = clientMargins.cxLeftWidth + 2;
    CVisual* iconVisual = window->iconVisual();
    if (iconVisual) {
        MARGINS iconMargins = iconVisual->insetMargins();
        SIZE iconSize = iconVisual->visualSize();
        if (windowData->hasIcon() || window->iconTest() == 0) {
            iconSize.cx = GetSystemMetricsForDpi(SM_CXSMICON, dpiValue);
            iconSize.cy = GetSystemMetricsForDpi(SM_CYSMICON, dpiValue);
            iconVisual->editVisualSize(iconSize);
        }
        iconMargins.cxLeftWidth = insetLeft;
        iconMargins.cyTopHeight = ((clientMargins.cyTopHeight - iconVisual->visualSize().cy) - borderSizes->cyTopHeight) / 2 + borderSizes->cyTopHeight;
        iconVisual->editInsetMargins(iconMargins);
        if (0 < iconVisual->visualSize().cx) insetLeft += iconVisual->visualSize().cx + 5;
        SetDirtyFlags(iconVisual, 2);
    }
    CVisual* textVisual = window->textVisual();
    if (textVisual) {
        MARGINS textMargins = textVisual->insetMargins();
        SIZE textSize = textVisual->visualSize();
        textMargins.cyTopHeight = borderSizes->cyTopHeight;
        if (settings.centerText) {
            WCHAR windowClass[256] = {};
            GetClassName(windowData->hWnd(), windowClass, 257);
            if (IsWindowClassValid(windowClass)) { 
                WCHAR windowName[256];
                GetWindowText(windowData->hWnd(), windowName, 257);
                Wh_Log(L"[i] we have [%s] of class [%s]", windowName, windowClass);
                if (wcslen(windowName)) textWidth = CalculateTextWidth(windowName, wcslen(windowName));
            }
            else { 
                Wh_Log(L"[x] window class [%s] has been declared illegal", windowClass);
                textMargins.cxLeftWidth = insetLeft;
                textMargins.cxRightWidth = insetRight;
                textVisual->editInsetMargins(textMargins);
                textWidth = 0;
            }
            if (textWidth) {
                textMargins.cxLeftWidth = (windowData->windowSize().cx / 2.0) - ((textWidth * (dpiValue / 96.0)) / 2.0);
                textMargins.cxRightWidth = textMargins.cxLeftWidth;
                //if the textVisual's right margin tries to overlap the caption buttons,
                //center it between the icon and caption buttons
                if (textMargins.cxRightWidth < insetRight) {
                    textMargins.cxLeftWidth -= (insetRight / 2.6);
                    if (textMargins.cxLeftWidth > insetLeft) textMargins.cxRightWidth += (insetRight / 2.7);
                    else textMargins.cxRightWidth = insetRight;
                }
                //dont let the textVisual overlap the icon
                if (textMargins.cxLeftWidth < insetLeft) textMargins.cxLeftWidth = insetLeft;
                textVisual->editInsetMargins(textMargins);
            }
        }
        else {
            textMargins.cxLeftWidth = insetLeft;
            textMargins.cxRightWidth = insetRight;
            textVisual->editInsetMargins(textMargins);
        }
        textSize.cy = clientMargins.cyTopHeight - borderSizes->cyTopHeight;
        textVisual->editVisualSize(textSize);
        SetDirtyFlags(textVisual, 2);
    }

    UpdatePinnedParts(window);
    return 0;
}
//HWND windowHandleCache;
//wchar_t textStringCache[256] = {};
CWindowData* (*FindWindowByHandle)(HWND handle);
long (*SetText)(BYTE* dwText, wchar_t* windowName);
long SetText_H(BYTE* dwText, wchar_t* windowName) {
    SetText(dwText, windowName);
    //textString -> HWND -> CWindowData -> CTopLevelWindow -> UpdateNCArea(PositionsAndSizes)
    //this contraption allows the center text function to work across titlebar text updates.
    if (settings.centerText) {
        HWND windowHandle = FindWindow(nullptr, windowName);
        WCHAR windowClass[256] = {};
        GetClassName(windowHandle, windowClass, 257);
        Wh_Log(L"[i] we have [%s] of class [%s]", windowName, windowClass);
        if (IsWindowClassValid(windowClass) && wcslen(windowName)) {
            CWindowData* windowData = FindWindowByHandle(windowHandle);
            CTopLevelWindow* window = reinterpret_cast<CTopLevelWindow* const*>(windowData)[55];
            UpdateNCArea_H(window);
        }
        else Wh_Log(L"[x] window class [%s] has been declared illegal", windowClass);
    }
    return 0;
}

// code region: frames
bool isMaximized;
bool isActive;
bool isTool;
int (*GetEffectiveCornerStyle)(CTopLevelWindow *window);
int GetEffectiveCornerStyle_H(CTopLevelWindow *window) {
    isMaximized = window->isMaximized();
    isActive = window->isActive();
    isTool = window->isTool();
    if (window->isWindow()) return 0; //this is important for SetBorderParameters
    else return GetEffectiveCornerStyle(window);  
}
float (*SetBorderParameters)(BYTE *windowBorder, tagRECT *rect, float radius, int dpi, _D3DCOLORVALUE *color, void* borderStyle, void* shadowStyle);
float SetBorderParameters_H(BYTE *windowBorder, tagRECT *rect, float radius, int dpi, _D3DCOLORVALUE *color, void* borderStyle, void* shadowStyle) {
    color->a = 0;
    //Wh_Log(L"[?] are you a window?");
    //Wh_Log(L"[#] border radius %f", radius);
    //Wh_Log(L"[#] border color %fR %fG %fB %fA", color->r, color->g, color->b, color->a);
    dpi = 96;
    if (color->r > 0.0 && color->g > 0.0 && color->b > 0.0) {
        //Wh_Log(L"   [x] no, im a context menu popup");
        radius = 0;
    }
    else if (radius == 4) {
        //Wh_Log(L"   [x] no, im the default win11 taskbar window preview label");
        radius = 0;
    }
    else if (radius == 0 && !isMaximized && !isTool) {
        //this is why the window condition returns 0 in GetEffectiveCornerStyle,
        //everything that calls SetBorderParameters has some radius by default
        //...everything except maximized windows...
        //Wh_Log(L"   [!] yes, i am a window");
        radius = (float)settings.windowRadius / 10;
    }
    //else Wh_Log(L"  [x] no, i'm a secret");
    return SetBorderParameters(windowBorder, rect, radius, dpi, color, borderStyle, shadowStyle);
}
bool contrastTrick = true;
bool (*IsHighContrastMode)();
bool IsHighContrastMode_H() {
    return contrastTrick;
}
int thinFrameExtra;
bool (*SetMargin)(struct _MARGINS*, int, int, int, int, struct _MARGINS const*);
int* (*GetBorderRect)(CTopLevelWindow *window, RECT* borderRect);
int* GetBorderRect_H(CTopLevelWindow *window, RECT* borderRect) {
    int* border = GetBorderRect(window, borderRect);    
    CWindowData* windowData = window->windowData();
    DWORD dwStyle = windowData->windowStyle();
    DWORD dwExStyle = windowData->windowStyleEx();
    int dpiValue = windowData->dpiValue();
    MARGINS windowMargins = windowData->frameMargins();
    //Wh_Log(L"windowMargins are %iL, %iR, %iT, %iB", windowMargins.cxLeftWidth,
     //windowMargins.cxRightWidth, windowMargins.cyTopHeight, windowMargins.cyBottomHeight);

    // CalculateOutsideMargins - simplified
    RECT thickFrameRect = {};
    AdjustWindowRectExForDpi(&thickFrameRect, dwStyle | 0x40000, 0, dwExStyle, dpiValue);
    //Wh_Log(L"the Rect angle: %iL, %iR, %iT, %iB", thickFrameRect.left, thickFrameRect.right, thickFrameRect.top, thickFrameRect.bottom);
    MARGINS thickFrameMargins  = {
        windowMargins.cxLeftWidth + thickFrameRect.left,
        windowMargins.cxRightWidth + -thickFrameRect.right,
        windowMargins.cyTopHeight + thickFrameRect.top,
        windowMargins.cyBottomHeight + -thickFrameRect.bottom
    };
    //Wh_Log(L"thickFrameMargins are %iL, %iR, %iT, %iB", thickFrameMargins.cxLeftWidth,
     //thickFrameMargins.cxRightWidth, thickFrameMargins.cyTopHeight, thickFrameMargins.cyBottomHeight);

    if (windowMargins.cxLeftWidth > 0 && windowMargins.cxRightWidth > 0 && windowMargins.cyTopHeight > 0 && windowMargins.cyBottomHeight > 0) {
        SetMargin((struct _MARGINS*)(window + pmoBorderMargins), thickFrameMargins.cxLeftWidth,
         thickFrameMargins.cxRightWidth, thickFrameMargins.cyTopHeight, thickFrameMargins.cyBottomHeight, 0); 
        //extend border rect or else the window frame will look weird
        borderRect->left += thickFrameMargins.cxLeftWidth;
        borderRect->top += thickFrameMargins.cyTopHeight;
        borderRect->right += -thickFrameMargins.cxRightWidth;
        borderRect->bottom += -thickFrameMargins.cyBottomHeight;
        thinFrameExtra = thickFrameMargins.cxLeftWidth;
    }
    //modify some random parameter to force the border to show up instantly
    //the window does not visually change (because DWM keeps reverting it)
    if (pmoWindowData == 752) *((int *)window + 160) = 1;
    return border;
}
bool updateSignal;
void (*OnSystemBackdropUpdated)(CTopLevelWindow* window);
int (*CalculateBackgroundType)(CTopLevelWindow* window);
int CalculateBackgroundType_H(CTopLevelWindow* window) {
    int backgroundType = CalculateBackgroundType(window);
    if (!settings.micaMode) {
        //workaround for DWM ColorPrevalence being disabled
        if (backgroundType >= 2 && backgroundType <= 4) return 0;
    }
    else {
        CWindowData* windowData = window->windowData();
        if (!windowData) return 0; //the object has no window data
        if (!window->isWindow()) return 0; //the object is not a window
        if (windowData->isAccentPolicyActive(windowData->accentPolicy())) return 1; //the window has an accent policy
        if (!window->systemBackdrop() || (updateSignal && window->isWindow())) {
            if (windowData->isDarkMode() != settings.darkMode) windowData->setDarkMode(settings.darkMode);
            if (!settings.micaSync) {
                if (settings.micaRich && windowData->backgroundType() != 4) {
                    windowData->setBackgroundType(4);
                    OnSystemBackdropUpdated(window);
                }                
                if (!settings.micaRich && windowData->backgroundType() != 2) {
                    windowData->setBackgroundType(2);
                    OnSystemBackdropUpdated(window);
                }
            }
        }
        if (settings.micaSync) {
            if (window->isActive() && windowData->backgroundType() != 4) {
                windowData->setBackgroundType(4);
                OnSystemBackdropUpdated(window);
            } 
            if (!window->isActive() && windowData->backgroundType() != 2) {
                windowData->setBackgroundType(2);
                OnSystemBackdropUpdated(window);
            }
        }
        if (settings.vistaBlackMax) {
            if (window->isMaximized() && !windowData->isDarkMode()) {
                windowData->setDarkMode(1);
                OnSystemBackdropUpdated(window);
            }
            if (!window->isMaximized() && windowData->isDarkMode()) {
                windowData->setDarkMode(0);
                OnSystemBackdropUpdated(window);
            }
        }
        //workaround for DWM ColorPrevalence being enabled
        if (backgroundType == 3) backgroundType = 2;
    }
    return backgroundType;
}
long (*SetState)(CVisual* backdropVisual, int backdropState, bool b2);
long SetState_H(CVisual* backdropVisual, int backdropState, bool b2) {
    if (settings.micaMode && settings.micaSync) backdropState = 1;
    return SetState(backdropVisual, backdropState, b2);
}
long (*UpdateSystemBackdropVisual)(CTopLevelWindow* window);
long UpdateSystemBackdropVisual_H(CTopLevelWindow* window) {
    if (!settings.micaMode) return UpdateSystemBackdropVisual(window);;
    contrastTrick = false;
    UpdateSystemBackdropVisual(window);
    contrastTrick = true;
    CWindowData* windowData = window->windowData();
    SIZE windowSize = windowData->windowSize();
    CVisual* backdrop = window->systemBackdrop();
    //Wh_Log(L"the window has backdrop type %i", window->systemBackdropType());
    if (backdrop && window->systemBackdropType()) {
        MARGINS backdropMargins = backdrop->insetMargins();
        SIZE backdropSize = backdrop->visualSize();
        if (thinFrameExtra < 0) {
            backdropMargins.cxLeftWidth += thinFrameExtra;
            backdropMargins.cxRightWidth += thinFrameExtra;
            backdropMargins.cyTopHeight += thinFrameExtra;
            if (backdropMargins.cyBottomHeight <= 0) backdropMargins.cyBottomHeight += thinFrameExtra;
            backdrop->editInsetMargins(backdropMargins);
        }
        //Wh_Log(L"backdropMargins are %iL, %iR, %iT, %iB", backdropMargins.cxLeftWidth,
         //backdropMargins.cxRightWidth, backdropMargins.cyTopHeight, backdropMargins.cyBottomHeight);
        if (backdropSize.cx != windowSize.cx && backdropSize.cx != windowSize.cx - (thinFrameExtra * 2)) {  
            backdropSize.cx = (windowSize.cx - (thinFrameExtra * 2));
            backdropSize.cy = (windowSize.cy - (thinFrameExtra * 2));
            backdrop->editVisualSize(backdropSize);
        }
    }
    return 0;
}
// code region: colors
long (*SetColor)(byte* dwText, unsigned long colorData);
long SetColor_H(byte* dwText, unsigned long colorData) {
    if (settings.textColor && isActive) colorData = (settings.textColorB << 16) + (settings.textColorG << 8) + settings.textColorR;
    if (settings.textColor2 && !isActive) colorData = (settings.textColorB2 << 16) + (settings.textColorG2 << 8) + settings.textColorR2;
    if (settings.vistaBlackMax && isMaximized) colorData = 4294967295;
    return SetColor(dwText, colorData);
}
long (*SolidColorBrushProxyUpdate)(void* brushProxy, double d2, _D3DCOLORVALUE color);
long SolidColorBrushProxyUpdate_H(void* brushProxy, double d2, _D3DCOLORVALUE color) {
    if (settings.vistaBlackMax && isMaximized) color.a = 1000;
    else color.a = settings.totalAlpha / 100;
    return SolidColorBrushProxyUpdate(brushProxy, d2, color);
}
long (*AdjustWindowColorization)(GpCC* glasscolor1, GpCC *glasscolor2, float opacityBalance, byte flag);
long AdjustWindowColorization_H(GpCC* glasscolor1, GpCC *glasscolor2, float opacityBalance, byte flag) {
    if (settings.colorScience) { //the first colorset is the colorization color itself
        Wh_Log(L"[1] gc1-raw: %iR, %iG, %iB, %iA", glasscolor1->r, glasscolor1->g, glasscolor1->b, glasscolor1->a);
        glasscolor1->r = settings.red1;
        glasscolor1->g = settings.green1;
        glasscolor1->b = settings.blue1;
        glasscolor1->a = settings.alpha1;
        Wh_Log(L"[1] gc1-mod: %iR, %iG, %iB, %iA", glasscolor1->r, glasscolor1->g, glasscolor1->b, glasscolor1->a);
    }
    if (settings.colorScience2) { //the second colorset is the background "behind" the colorization color
        Wh_Log(L"[2] gc2-raw: %iR, %iG, %iB, %iA", glasscolor2->r, glasscolor2->g, glasscolor2->b, glasscolor2->a);
        glasscolor2->r = settings.red2;
        glasscolor2->g = settings.green2;
        glasscolor2->b = settings.blue2;
        glasscolor2->a = settings.alpha2;
        Wh_Log(L"[2] gc2-mod: %iR, %iG, %iB, %iA", glasscolor2->r, glasscolor2->g, glasscolor2->b, glasscolor2->a);
    }
    if (settings.vistaBlackMax && isMaximized) {
        opacityBalance = 0.4;
        glasscolor1->a = 255;
        glasscolor2->r = 0;
        glasscolor2->g = 0;
        glasscolor2->b = 0;
        glasscolor2->a = 255;
    }
    return AdjustWindowColorization(glasscolor1, glasscolor2, opacityBalance, flag);
}
// code region: shadows
int (*GetShadowStyle)(CTopLevelWindow* window);
int GetShadowStyle_H(CTopLevelWindow* window){
    int shadow = GetShadowStyle(window);
    Wh_Log(L"[i] shadow style type %i", shadow);
    if (!window->isWindow()) return shadow;
    if (window->isMaximized()) return 0;
    if (window->isActive()) shadow = 2;
    else if (!window->isActive()) shadow = 3;
    return shadow;
}
void (*GetShadowParameters)(int shadow, int DPI, float* sqSize, float* stretchSize, float* shadowOpacityWeird, float* shadowOpacity);
void GetShadowParameters_H(int shadow, int DPI, float* sqSize, float* stretchSize, float* shadowOpacityWeird, float* shadowOpacity) {
    if (settings.disableShadows) return;
    if (shadow == 1) {
        Wh_Log(L"[i] category 1: context menus");
        *sqSize = settings.sqSize1;
        *shadowOpacityWeird = settings.shadowOpacityWeird1 / 100;
    }
    else if (shadow == 2) {
        Wh_Log(L"[i] category 2: active window");
        *sqSize = settings.sqSize2;
        *stretchSize = settings.stretchSize2;
        *shadowOpacityWeird = settings.shadowOpacityWeird2 / 100;
        *shadowOpacity = settings.shadowOpacity2 / 100;
    }
    else if (shadow == 3) {
        Wh_Log(L"[i] category 3: inactive window");
        *sqSize = settings.sqSize3;
        *stretchSize = settings.stretchSize3;
        *shadowOpacityWeird = settings.shadowOpacityWeird3 / 100;
        *shadowOpacity = settings.shadowOpacity3 / 100;
    }
    else {
        Wh_Log(L"[?] category %i: i dont know", shadow);
        *sqSize = settings.sqSize4;
        *stretchSize = settings.stretchSize4;
        *shadowOpacityWeird = settings.shadowOpacityWeird4 / 100;
        *shadowOpacity = settings.shadowOpacity4 / 100;
    }
}

long (*WINAPI SetVisualStates)(BYTE *buttonData, void *bitmapSource1, void *bitmapSource2, float opacity);
long WINAPI SetVisualStates_H(BYTE *buttonData, void *bitmapSource1, void *bitmapSource2, float opacity) {
  return SetVisualStates(buttonData, bitmapSource1, bitmapSource2, 1.0f);
}
void (*RtlGetVersion)(LPOSVERSIONINFOEXW);
OSVERSIONINFOEXW versionInfo;
wchar_t versionName[16] = {};
//detect which version of Windows 11 the mod is running on and
//adjust the "pointer math" offsets to the proper values, if necessary
bool AdjustParametersForVersion() {
    *(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandle(L"ntdll.dll"), "RtlGetVersion");
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
    RtlGetVersion(&versionInfo);
    int build = versionInfo.dwBuildNumber;
    Wh_Log(L"[i] the build number is %i", build);
    if (build < 22000) {
        Wh_Log(L"[?] not Windows 11");
        return false;
    }
    else if (build >= 22000 && build < 22621) {
        Wh_Log(L"[x] Windows 11 21H2");
        return false;
    }
    else if (build >= 22621 && build < 22631) {
        Wh_Log(L"[i] Windows 11 22H2");
    }
    else if (build >= 22631 && build < 26100) {
        Wh_Log(L"[i] Windows 11 23H2");
    }
    else if (build >= 26100 && build < 27000) {
        Wh_Log(L"[i] Windows 11 24H2");
        pmoWindowData = 712;
        pmoSystemBackdrop = 280;
        pmoSystemBackdropType = 800;
        pmoState1 = 200;
        pmoState2 = 584;
        pmoVisualSize = 72;
        pmoVisualMargins = 80;
        pmoClientMargins = 588;
        pmoBorderMargins = 620;
        pmoBorderMarginsMax = 636;
        pmoClientTest = 480;
        pmoClientVisual = 552;
        pmoButtonVisual = 488;
        pmoIconVisual = 536;
        pmoTextVisual = 520;
        pmoUnknownVisual = 296;
    }
    else {
        Wh_Log(L"[x] a Canary build");
        return false;
    }
    return true;
}
BOOL Wh_ModInit() {
    if (*(USHORT*)((BYTE*)NtCurrentTeb() + 0x17EE) & 0x0400) {
        Wh_Log(L"[x] dwm crashed");
        return FALSE;
    }
    if (!AdjustParametersForVersion()) {
        Wh_Log(L"[x] OS version incompatibility");
        MessageBeep(MB_ICONERROR);
        return false;
    }
    LoadSettings();
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {L"private: long __cdecl CTopLevelWindow::UpdateNCAreaPositionsAndSizes(void)"},
            (void**)&UpdateNCArea,
            (void*)UpdateNCArea_H,
        },
        {
            {L"private: long __cdecl CTopLevelWindow::UpdatePinnedParts(void)"},
            (void**)&UpdatePinnedParts,
            nullptr,
        },
        {
            {L"public: virtual long __cdecl CDWriteText::SetText(unsigned short const *)"},
            (void**)&SetText,
            (void*)SetText_H,
        },
        {
            {L"private: static class CWindowData * __cdecl CMagnifierControl::FindWindowByHandle(struct HWND__ *)"},
            (void**)&FindWindowByHandle,
            nullptr,
        },
        {
            {L"public: virtual void __cdecl CVisual::SetDirtyFlags(unsigned long)"},
            (void**)&SetDirtyFlags,
            nullptr,
        },
        {
            {L"private: enum CORNER_STYLE __cdecl CTopLevelWindow::GetEffectiveCornerStyle(void)"},
            (void**)&GetEffectiveCornerStyle,
            (void*)GetEffectiveCornerStyle_H,
        },
        {
            {L"public: long __cdecl CWindowBorder::SetBorderParameters(struct tagRECT const &,float,int,struct _D3DCOLORVALUE const &,enum CWindowBorder::BorderStyle,enum CWindowBorder::ShadowStyle)"},
            (void**)&SetBorderParameters,
            (void*)SetBorderParameters_H,
        },
        {
            {L"public: struct tagRECT __cdecl CTopLevelWindow::GetBorderRect(bool)const "},
            (void**)&GetBorderRect,
            (void*)GetBorderRect_H,
        },
        {
            {L"bool __cdecl SetMargin(struct _MARGINS *,int,int,int,int,struct _MARGINS const *)"},
            (void**)&SetMargin,
            nullptr,
        },
        {
            {L"public: static bool __cdecl CDesktopManager::IsHighContrastMode(void)"},
            (void**)&IsHighContrastMode,
            (void*)IsHighContrastMode_H,
        },
        {
            {L"private: enum CTopLevelWindow::BackgroundType __cdecl CTopLevelWindow::CalculateBackgroundType(void)const "},
            (void**)&CalculateBackgroundType,
            (void*)CalculateBackgroundType_H,
        },
        {
            {L"private: long __cdecl CTopLevelWindow::UpdateSystemBackdropVisual(void)"},
            (void**)&UpdateSystemBackdropVisual,
            (void*)UpdateSystemBackdropVisual_H,
        },
        {
            {L"public: void __cdecl CTopLevelWindow::OnSystemBackdropUpdated(void)"},
            (void**)&OnSystemBackdropUpdated,
            nullptr,
        },
        {
            {L"private: bool __cdecl CTopLevelWindow::TreatAsActiveWindow(void)const "},
            (void**)&TreatAsActiveWindow,
            nullptr,
        },
        {
            {L"public: long __cdecl CSolidColorLegacyMilBrushProxy::Update(double,struct _D3DCOLORVALUE const &)"},
            (void**)&SolidColorBrushProxyUpdate,
            (void*)SolidColorBrushProxyUpdate_H,
        },
        {
            {L"public: virtual void __cdecl CDWriteText::SetColor(unsigned long)"},
            (void**)&SetColor,
            (void*)SetColor_H,
        },
        {
            {L"public: void __cdecl CGlassColorizationParameters::AdjustWindowColorization(union GpCC const *,float,struct TMILFlagsEnum<enum ColorizationFlags::FlagsEnum>)"},
            (void**)&AdjustWindowColorization,
            (void*)AdjustWindowColorization_H,
        },
        {
            {L"private: enum CWindowBorder::ShadowStyle __cdecl CTopLevelWindow::GetShadowStyle(void)"},
            (void**)&GetShadowStyle,
            (void*)GetShadowStyle_H,
        },
        {
            {L"private: static void __cdecl CWindowBorder::GetShadowParameters(enum CWindowBorder::ShadowStyle,int,float *,float *,float *,float *)"},
            (void**)&GetShadowParameters,
            (void*)GetShadowParameters_H,
        },        
        {
            {L"public: long __cdecl CButton::SetVisualStates(class CBitmapSourceArray const &,class CBitmapSourceArray const &,float)"},
            (void**)&SetVisualStates,
            (void*)SetVisualStates_H,
        }
    };
    WindhawkUtils::SYMBOL_HOOK versionDependentHooks[] = {
        {
            {L"private: long __cdecl CSystemBackdropVisual::SetState(enum CSystemBackdropVisual::BackdropState,bool)"},
            (void**)&SetState,
            (void*)SetState_H,
        }
    };
    if (pmoWindowData == 712) versionDependentHooks[0] = 
        {
            {L"private: long __cdecl CSystemBackdropVisual::SetState(enum CSystemBackdropVisual::BackdropState,bool,bool)"},
            (void**)&SetState,
            (void*)SetState_H,
        };
    if (HookSymbols(GetModuleHandle(L"udwm.dll"), symbolHooks, ARRAYSIZE(symbolHooks))) {
        if (HookSymbols(GetModuleHandle(L"udwm.dll"), versionDependentHooks, ARRAYSIZE(versionDependentHooks))) {
            Wh_Log(L"[i] the mod started successfully");
            return true;
        }
        else {
            Wh_Log(L"[x] version-dependent function hooking failed, a symbol name may have changed.");
            return false;
        }
    }
    else {
        Wh_Log(L"[x] function hooking failed, are the symbols up-to-date?");
        return false;
    }
}
void Wh_ModSettingsChanged() {
    LoadSettings();
    updateSignal = true;
    PostMessage(FindWindow(L"Dwm", nullptr), WM_THEMECHANGED, 0, 0);
    Sleep(2000);
    updateSignal = false;
}
void Wh_ModAfterInit() {
    updateSignal = true;
    PostMessage(FindWindow(L"Dwm", nullptr), WM_THEMECHANGED, 0, 0);
    Sleep(2000);
    updateSignal = false;
}