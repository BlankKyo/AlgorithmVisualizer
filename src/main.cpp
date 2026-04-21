#include <QApplication>
#include "ui/MainWindow.h"
#include "utils/Logger.h"


// ─────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────
LogLevel parseLogLevel(const std::string& s) {
    if (s == "DEBUG")   return LogLevel::DEBUG;
    if (s == "WARNING") return LogLevel::WARNING;
    if (s == "ERROR")   return LogLevel::ERROR;
    return LogLevel::INFO;
}

static const char* TAG = "Main";

int main(int argc, char* argv[]) {

    // ── Logger ────────────────────────────────────────────
    std::string logFile  = "logs/algo.log";
    std::string logLevel = "INFO";
    try {
        Logger::instance().init(logFile, parseLogLevel(logLevel));
    } catch (const std::exception& e) {
        LOG_WARNING(TAG, "Failed to initialize logger: " + std::string(e.what()));
    }

    QApplication app(argc, argv);
    app.setApplicationName("Algorithm Visualizer");
    app.setApplicationVersion("1.0");

    MainWindow window;
    window.show();

    return app.exec();
}