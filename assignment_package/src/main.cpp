#include <mainwindow.h>

#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>
#include <QPalette>

void debugFormatVersion()
{
    QSurfaceFormat form = QSurfaceFormat::defaultFormat();
    QSurfaceFormat::OpenGLContextProfile prof = form.profile();

    const char *profile =
        prof == QSurfaceFormat::CoreProfile ? "Core" :
        prof == QSurfaceFormat::CompatibilityProfile ? "Compatibility" :
        "None";

    printf("Requested format:\n");
    printf("  Version: %d.%d\n", form.majorVersion(), form.minorVersion());
    printf("  Profile: %s\n", profile);
}

int main(int argc, char *argv[])
{

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    // dark style palette
    a.setStyle("Fusion");
    QPalette palette = QPalette();
    palette.setColor(palette.Window, QColor(53, 53, 53));
    palette.setColor(palette.WindowText, QColor(255, 255, 255));
    palette.setColor(palette.Base, QColor(25, 25, 25));
    palette.setColor(palette.AlternateBase, QColor(53, 53, 53));
    palette.setColor(palette.ToolTipBase, QColor(255, 255, 255));
    palette.setColor(palette.ToolTipText, QColor(255, 255, 255));
    palette.setColor(palette.Text, QColor(255, 255, 255));
    palette.setColor(palette.Button, QColor(53, 53, 53));
    palette.setColor(palette.ButtonText, QColor(255, 255, 255));
    palette.setColor(palette.BrightText, QColor(255, 0, 0));
    palette.setColor(palette.Link, QColor(42, 130, 218));
    palette.setColor(palette.Highlight, QColor(42, 130, 218));
    palette.setColor(palette.HighlightedText, QColor(0, 0, 0));
    a.setPalette(palette);

    // Set OpenGL 3.2 and, optionally, 4-sample multisampling
    QSurfaceFormat format;
    format.setVersion(3, 2);
    format.setOption(QSurfaceFormat::DeprecatedFunctions, false);
    format.setProfile(QSurfaceFormat::CoreProfile);
    //format.setSamples(4);  // Uncomment for nice antialiasing. Not always supported.

    /*** AUTOMATIC TESTING: DO NOT MODIFY ***/
    /*** Check whether automatic testing is enabled */
    /***/ if (qgetenv("CIS277_AUTOTESTING") != nullptr) format.setSamples(0);

    QSurfaceFormat::setDefaultFormat(format);
    debugFormatVersion();

    MainWindow w;
    w.show();

    return a.exec();
}
