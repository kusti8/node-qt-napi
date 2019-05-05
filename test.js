const qt = require("./lib/qt");
const app = new qt.QApplication();
const window = new qt.QMainWindow();
const box = new qt.QWidget(window);
box.setStyleSheet("background-color:black;");
box.resize(300, 300);
box.move(300, 300);
window.show();
app.exec();
