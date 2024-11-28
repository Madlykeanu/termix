#include <QApplication>
#include "gui/mainwindow.h"
#include "utils/config.h"
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize logging
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    spdlog::set_level(spdlog::level::debug);

    // Load configuration
    if (!termix::utils::Config::getInstance().loadFromFile("config.json")) {
        spdlog::warn("No configuration file found or failed to load. Using defaults.");
    }

    // Create and show main window
    termix::MainWindow window;
    window.show();

    return app.exec();
}
