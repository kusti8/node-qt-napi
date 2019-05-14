{
  "targets": [
    {
      "target_name": "qt",
      "sources": [
        "<!(QT_SELECT=5 moc src/QtGui/qapplication.hpp -o src/QtGui/qapplication.moc)",
        "src/qt.cpp",
        "src/QtGui/qapplication.cpp",
        "src/QtGui/qwidget.cpp",
        "src/QtGui/qmainwindow.cpp",
        "src/QtGui/qlabel.cpp",
        "src/misc.cpp",
        "src/utils/unwrapper.cpp",
      ],
      "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7"
      },
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 }
      },
      "conditions": [
        [
          "OS==\"mac\"",
          {
            "cflags+": ["-fvisibility=hidden"],
            "xcode_settings": {
              "GCC_SYMBOLS_PRIVATE_EXTERN": "YES"
            }
          }
        ],
        [
          "OS==\"linux\"",
          {
            "cflags": ["<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets)"],
            "ldflags": [
              "<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Widgets)"
            ],
            "libraries": ["<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Widgets)"]
          }
        ]
      ]
    }
  ]
}
