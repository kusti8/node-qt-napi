var binary = require('node-pre-gyp');
var path = require('path');
var binding_path = binary.find(
    path.resolve(path.join(__dirname, '../package.json'))
);
var oldpath = process.cwd();
process.chdir(path.dirname(binding_path));
process.env.QT_PLUGIN_PATH = path.dirname(binding_path);
var qt = require(binding_path);
process.chdir(oldpath);

qt.Alignment = {
    AlignLeft: 0x0001,
    AlignRight: 0x0002,
    AlignHCenter: 0x0004,
    AlignJustify: 0x0008,
    AlignTop: 0x0020,
    AlignBottom: 0x0040,
    AlignVCenter: 0x0080,
    AlignBaseline: 0x0100,
    AlignCenter: 0x0080 | 0x0004,
    AlignAbsolute: 0x0010,
    AlignLeading: 0x0001,
    AlignTrailing: 0x0002,
};
Object.freeze(qt.Alignment);

qt.AspectRatioMode = {
    IgnoreAspectRatio: 0,
    KeepAspectRatio: 1,
    KeepAspectRatioByExpanding: 2,
};
Object.freeze(qt.AspectRatioMode);

qt.WindowType = {
    Widget: 0x00000000,
    Window: 0x00000001,
    SubWindow: 0x00000012,

    WindowType_Mask: 0x000000ff,
    MSWindowsFixedSizeDialogHint: 0x00000100,
    MSWindowsOwnDC: 0x00000200,
    BypassWindowManagerHint: 0x00000400,
    FramelessWindowHint: 0x00000800,
    WindowTitleHint: 0x00001000,
    WindowSystemMenuHint: 0x00002000,
    WindowMinimizeButtonHint: 0x00004000,
    WindowMaximizeButtonHint: 0x00008000,
    WindowContextHelpButtonHint: 0x00010000,
    WindowShadeButtonHint: 0x00020000,
    WindowStaysOnTopHint: 0x00040000,
    WindowTransparentForInput: 0x00080000,
    WindowOverridesSystemGestures: 0x00100000,
    WindowDoesNotAcceptFocus: 0x00200000,
    MaximizeUsingFullscreenGeometryHint: 0x00400000,

    CustomizeWindowHint: 0x02000000,
    WindowStaysOnBottomHint: 0x04000000,
    WindowCloseButtonHint: 0x08000000,
    MacWindowToolBarButtonHint: 0x10000000,
    BypassGraphicsProxyWidget: 0x20000000,
    NoDropShadowWindowHint: 0x40000000,
    WindowFullscreenButtonHint: 0x80000000
};
qt.WindowType = {
    ...qt.WindowType,
    Dialog: 0x00000002 | qt.WindowType.Window,
    Sheet: 0x00000004 | qt.WindowType.Window,
    Popup: 0x00000008 | qt.WindowType.Window,
    Desktop: 0x00000010 | qt.WindowType.Window,
    ForeignWindow: 0x00000020 | qt.WindowType.Window,
    CoverWindow: 0x00000040 | qt.WindowType.Window,
    X11BypassWindowManagerHint: qt.WindowType.BypassWindowManagerHint,
    WindowMinMaxButtonsHint: qt.WindowType.WindowMinimizeButtonHint | qt.WindowType.WindowMaximizeButtonHint,
};
qt.WindowType = {
    ...qt.WindowType,
    Drawer: qt.WindowType.Sheet | qt.WindowType.Dialog,
    Tool: qt.WindowType.Popup | qt.WindowType.Dialog,
    ToolTip: qt.WindowType.Popup | qt.WindowType.Sheet,
    SplashScreen: qt.WindowType.Popup | qt.WindowType.Sheet | qt.WindowType.Dialog,
}
Object.freeze(qt.WindowType);

module.exports = qt;
