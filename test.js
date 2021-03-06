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
box.setMouseTracking(true);
box.mouseMoveEvent((x, y) => console.log(`MOUSE MOVED! x: ${x} y: ${y}`));
box.enterEvent(() => console.log("MOUSE ENTERED!"));
box.leaveEvent(() => console.log("MOUSE LEFT!"));
const label = new qt.QLabel(box);
console.log("Size hint", label.sizeHint());
console.log("Height", label.height());
label.setText('<span style="">dsawewwww<span style="">Hello2</span></span>');
label.adjustSize();
const label2 = new qt.QLabel(window);
const pix = new qt.QPixmap();
pix.load("/home/kusti8/Pictures/test_small.jpg");
pix.scaled(300, 300, qt.AspectRatioMode.IgnoreAspectRatio);
label2.setPixmap(pix);
label2.adjustSize();
label2.setStyleSheet("background-color: red;");
label2.move(300, 600);
label2.setScaledContents(false);
label2.setAlignment(qt.Alignment.AlignCenter);
label2.show();
const lineedit = new qt.QLineEdit(window);
lineedit.move(100, 100);
lineedit.textChangedEvent(text => console.log("text changed", text));
lineedit.show();
const combobox = new qt.QComboBox(window);
combobox.currentTextChangedEvent(text => console.log("New combo", text));
combobox.setEditable(true);
combobox.addItem("Test1");
combobox.addItem("Test2");
combobox.addItem("Test3");
box.show();
console.log("set parent");
window.show();
console.log("set parent");
app.aboutToQuitEvent(() => console.log("Quitting"));
console.log("Height", label.height());
console.log(qt.desktopSize());
app.exec();
