const qt = require("./lib/qt");
const app = new qt.QApplication();
const window = new qt.QMainWindow();
const box = new qt.QWidget();
box.setStyleSheet("background-color:black;");
box.resize(300, 300);
box.move(300, 300);
box.setParent(window);
window.resizeEvent((width, height) => {
  console.log("Resized1", width, height);
  console.log(width, height);
});
window.closeEvent(() => {
  console.log("Closing");
});
box.resizeEvent((width, height) => {
  console.log("Resized2", width, height);
});
box.show();
console.log("set parent");
window.show();
console.log("set parent");
app.exec();
