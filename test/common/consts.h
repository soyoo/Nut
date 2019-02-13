#ifndef CONSTS_H
#define CONSTS_H

#define REGISTER(x) qDebug() << (#x) << "type id:" << qMetaTypeId<x*>()
#define PRINT(x) qDebug() << (#x "=") << (x);
#define TIC()  QElapsedTimer timer; timer.start()
#define TOC()  qDebug() << QString("Elapsed time: %1ms for %2") \
    .arg(timer.elapsed() / 1000.) \
    .arg(__func__)

#define DRIVER "QMYSQL"
#define DATABASE QString(metaObject()->className()).toLower() + "_db"
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""

#ifdef Q_OS_LINUX
#   define OS "Linux"
#elif defined(Q_OS_WIN)
#   define OS "Windows"
#elif defined(Q_OS_OSX)
#   define OS "macOS"
#else
#   define OS "Unknown"
#endif

#define PRINT_FORM(db) \
    qDebug() << "\n\n****************************"                             \
             << "\nAll tests passed,"                                          \
             << "please fill in bellow form and email it to me at"             \
             << "hamed.masafi@gmail.com"                                       \
             << "\n\tDriver:" << db.driver()                                   \
             << "\n\tOS: " OS " (version: ________)"                           \
             << "\n\tQt version: " QT_VERSION_STR                              \
             << "\n\tTest:" << metaObject()->className()                       \
             << "\n****************************\n";


#endif // CONSTS_H
