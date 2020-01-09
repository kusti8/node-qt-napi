{
    "targets": [
        {
            "target_name": "<(module_name)",
            "sources": [
                "src/qt.cpp",
                "src/QtGui/qapplication.cpp",
                "src/QtGui/qwidget.cpp",
                "src/QtGui/qmainwindow.cpp",
                "src/QtGui/qlabel.cpp",
                "src/QtGui/qlineedit.cpp",
                "src/QtGui/qpixmap.cpp",
                "src/QtGui/qcombobox.cpp",
                "src/QtGui/qplaintextedit.cpp",
                "src/QtGui/qpushbutton.cpp",
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
            "defines": [
                "NAPI_VERSION=<(napi_build_version)",
            ],
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1}
            },
            "conditions": [
                [
                    "OS==\"mac\"",
                    {
                        "cflags+": ["-fvisibility=hidden"],
                        "xcode_settings": {
                            "GCC_SYMBOLS_PRIVATE_EXTERN": "YES"
                        },
                        'include_dirs': [
                            'deps/5.12.3/darwin/include',
                            'deps/5.12.3/darwin/include/QtCore',
                            'deps/5.12.3/darwin/include/QtGui',
                            'deps/5.12.3/darwin/include/QtWidgets'
                        ],
                        'libraries': [
                            '../deps/5.12.3/darwin/lib/QtCore.framework/QtCore',
                            '../deps/5.12.3/darwin/lib/QtGui.framework/QtGui',
                            '../deps/5.12.3/darwin/lib/QtWidgets.framework/QtWidgets',
                        ]
                    }
                ],
                [
                    "OS==\"linux\"",
                    {
                        "sources": [
                            "<!(moc src/QtGui/qapplication.hpp -o src/QtGui/qapplication.moc)",
                            "<!(moc src/QtGui/qlineedit.hpp -o src/QtGui/qlineedit.moc)",
                            "<!(moc src/QtGui/qcombobox.hpp -o src/QtGui/qcombobox.moc)",
                            "<!(moc src/QtGui/qplaintextedit.hpp -o src/QtGui/qplaintextedit.moc)",
                            "<!(moc src/QtGui/qpushbutton.hpp -o src/QtGui/qpushbutton.moc)",
                            "src/QtGui/qapplication.cpp",
                            "src/QtGui/qlineedit.cpp",
                            "src/QtGui/qcombobox.cpp",
                            "src/QtGui/qplaintextedit.cpp",
                            "src/QtGui/qpushbutton.cpp",
                        ],
                        "cflags": ["<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets)"],
                        "ldflags": [
                            "<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Widgets)"
                        ],
                        "libraries": ["<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Widgets)"],
                    }
                ],
                ['OS=="win"', {
                    'include_dirs': [
                        'deps/5.12.3/win32/include',
                        'deps/5.12.3/win32/include/QtCore',
                        'deps/5.12.3/win32/include/QtGui',
                        'deps/5.12.3/win32/include/QtWidgets',
                    ],
                    'libraries': [
                        # TODO: fix node-gyp behavior that requires ../
                        '../deps/5.12.3/win32/lib/Qt5Core.lib',
                        '../deps/5.12.3/win32/lib/Qt5Gui.lib',
                        '../deps/5.12.3/win32/lib/Qt5Widgets.lib',
                    ]
                }]
            ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": ["<(module_name)"],
            "copies": [
                {
                    "files": ["<(PRODUCT_DIR)/<(module_name).node"],
                    "destination": "<(module_path)"
                }
            ],
            'conditions': [
                ['OS == "win"', {
                    "copies": [
                        {
                            "files": [
                                "deps/5.12.3/win32/Qt5Core.dll",
                                "deps/5.12.3/win32/Qt5Gui.dll",
                                "deps/5.12.3/win32/Qt5Widgets.dll",
                                "deps/5.12.3/win32/vccorlib140.dll",
                                "deps/5.12.3/win32/msvcp140.dll",
                                "deps/5.12.3/win32/vcruntime140.dll"
                            ],
                            "destination": "<(module_path)"
                        },
                        {
                            "files": [
                                "deps/5.12.3/win32/platforms/qwindows.dll"
                            ],
                            "destination": "<(module_path)/platforms/"
                        }
                    ]
                }
                ],
                ['OS == "mac"', {
                    "copies": [
                        {
                            "files": [
                                "deps/5.12.3/darwin/lib",
                                "deps/5.12.3/darwin/platforms"
                            ],
                            "destination": "<(module_path)"
                        }
                    ]
                }]
            ]
        }
    ]
}
