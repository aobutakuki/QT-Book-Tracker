#include "QTBOOKMETER.h"
#include "LoginDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
   
    
   
    QApplication a(argc, argv);
    QFont font("Aptos Narrow");
    font.setStyleHint(QFont::Monospace);

    QApplication::setFont(font);
    a.setWindowIcon(QIcon("C:\\Users\\xanda\\source\\repos\\QTBOOKMETER\\images\\app_icon.png"));

 
    LoginDialog loginDialog;
    loginDialog.setStyleSheet("QDialog {background-color: #131121};");

    if (loginDialog.exec() == QDialog::Accepted) {

        QTBOOKMETER w;



        w.show();
        return a.exec();
    }

    return 0;

}
