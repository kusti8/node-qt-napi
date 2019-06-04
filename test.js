const qt = require("./lib/qt");
const app = new qt.QApplication();
const window = new qt.QMainWindow();
const box = new qt.QWidget();
box.setStyleSheet("background-color:red;");
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
box.mousePressEvent(() => console.log("CLICKED!"));
box.mouseReleaseEvent(() => console.log("UNCLICKED!"));
const label = new qt.QLabel(box);
console.log("Size hint", label.sizeHint());
console.log("Height", label.height());
label.setText('<span style="">dsawewwww<span style="">Hello2</span></span>');
label.adjustSize();
box.show();
console.log("set parent");
window.show();
console.log("set parent");
app.aboutToQuitEvent(() => console.log("Quitting"));
console.log("Height", label.height());
console.log(qt.desktopSize());
app.exec();
