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

module.exports = qt;
