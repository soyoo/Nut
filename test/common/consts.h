#ifndef CONSTS_H
#define CONSTS_H

#define PRINT(x) qDebug() << #x "=" << x;
#define TIC()  QElapsedTimer timer; timer.start()
#define TOC()  qDebug() << QString("Elapsed time: %1ms for %2") \
    .arg(timer.elapsed() / 1000.) \
    .arg(__func__)

//#define DRIVER "QPSQL"
//#define HOST "127.0.0.1"
//#define DATABASE "nutdb2"
//#define USERNAME "postgres"
//#define PASSWORD "856856"

#define DRIVER "QSQLITE"
#define HOST "127.0.0.1"
#define DATABASE "nutdb1"
//#define USERNAME "root"
//#define PASSWORD "onlyonlyi"

//#define DRIVER "QODBC"
//#define HOST "127.0.0.1"
//#define DATABASE "DRIVER={SQL Server};Server=.;Database=Nut2;Uid=sa;Port=1433;Pwd=qwe123!@#;WSID=."
//#define USERNAME "sa"
//#define PASSWORD "qwe123!@#"

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

#define TIC()  QElapsedTimer timer; timer.start()
#define TOC()  qDebug() << QString("Elapsed time: %1ms for %2") \
    .arg(timer.elapsed() / 1000.) \
    .arg(__func__)

#endif // CONSTS_H
