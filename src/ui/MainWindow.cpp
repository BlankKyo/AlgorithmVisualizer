// src/ui/MainWindow.cpp
#include "ui/MainWindow.h"
#include "ui/SortingWidget.h"
#include "engine/BubbleSortEngine.h"
#include "utils/RandomGenerator.h"
#include "utils/MemoryUtils.h"
#include <QMenuBar>
#include <QAction>

static const char* TAG = "MainWindow";

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Algorithm Visualizer");
    resize(1200, 800);
    LOG_DEBUG(TAG, MemoryUtils::formatLifecycleLog("Constructor", this, sizeof(*this)));

    setupUI();
    showHomePage();
}

MainWindow::~MainWindow() {
    LOG_DEBUG(TAG, MemoryUtils::formatLifecycleLog("Destructor", this, sizeof(*this)));
}

void MainWindow::setupUI() {
    // Create stacked widget
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    // Create home page
    m_homePage = new HomePage(this);
    m_stackedWidget->addWidget(m_homePage);

    // Create algorithm page
    m_algorithmPage = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(m_algorithmPage);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    // Algorithm widget placeholder (will be set when algorithm is selected)
    m_currentAlgorithmWidget = nullptr;

    // Controls bar
    auto* controls = new QHBoxLayout();

    m_backBtn = new QPushButton("← Back to Home", this);
    m_startBtn = new QPushButton("Start", this);
    m_pauseBtn = new QPushButton("Pause", this);
    m_resetBtn = new QPushButton("Reset", this);
    m_pauseBtn->setEnabled(false);

    auto* speedLabel = new QLabel("Speed:", this);
    m_speedSlider = new QSlider(Qt::Horizontal, this);
    m_speedSlider->setRange(1, 20);   // 1 = slow (500ms), 20 = fast (10ms)
    m_speedSlider->setValue(10);
    m_speedSlider->setFixedWidth(150);

    controls->addWidget(m_backBtn);
    controls->addWidget(m_startBtn);
    controls->addWidget(m_pauseBtn);
    controls->addWidget(m_resetBtn);
    controls->addStretch();
    controls->addWidget(speedLabel);
    controls->addWidget(m_speedSlider);

    mainLayout->addLayout(controls);

    m_stackedWidget->addWidget(m_algorithmPage);

    // Timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    // Connect signals
    connect(m_homePage, &HomePage::algorithmSelected, this, &MainWindow::onAlgorithmSelected);
    connect(m_backBtn, &QPushButton::clicked, this, &MainWindow::onBackToHome);
    connect(m_startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(m_pauseBtn, &QPushButton::clicked, this, &MainWindow::onPause);
    connect(m_resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);

    // Speed slider updates timer interval live
    connect(m_speedSlider, &QSlider::valueChanged, this, [this](int val) {
        int ms = 510 - val * 25;   // val=1 → 485ms, val=20 → 10ms
        m_timer->setInterval(ms);
    });
}

void MainWindow::onAlgorithmSelected(const QString& category, const QString& algorithm) {
    m_currentCategory = category;
    m_currentAlgorithm = algorithm;
    setupEngine(category, algorithm);
    showAlgorithmPage();
}

void MainWindow:: setupEngine(const QString& category, const QString& algorithm) {
    std::unique_ptr<AlgorithmEngine> engine;
    std::shared_ptr<std::vector<int>> data;

    
    if (category == "Sorting") {
        if (algorithm == "Bubble Sort") {
            engine = std::make_unique<BubbleSortEngine>();
            data = std::make_shared<std::vector<int>>(Random_Vector(int, 20, 10, 100));
        }
        // Add other sorting algorithms here as they are implemented
    }

    if (engine) {
        engine->initialize(data);

        // Wire the callback: engine fires → UI repaints
        engine->setStepCallback([this](const StepEvent& e) {
            applyStep(e);
        });

        m_engine = std::move(engine);

        // Create appropriate widget based on category
        if (category == "Sorting") {
            auto* sortingWidget = new SortingWidget(m_algorithmPage);
            sortingWidget->setData(data);
            

            // Add to layout (insert at top)
            auto* layout = qobject_cast<QVBoxLayout*>(m_algorithmPage->layout());
            if (layout && layout->count() > 0) {
                // 1. Safety Check: Only delete if it actually exists
                if (m_currentAlgorithmWidget) {
                    layout->removeWidget(m_currentAlgorithmWidget);
                    m_currentAlgorithmWidget->deleteLater(); 
                }

                // 2. Update the pointer to the NEW widget
                m_currentAlgorithmWidget = sortingWidget;

                // 3. Put it on screen
                layout->insertWidget(0, sortingWidget, 1);
            }
        }
    }
}

void MainWindow::applyStep(const StepEvent& event) {
    if (m_currentAlgorithmWidget) {
        m_currentAlgorithmWidget->highlight(event.indexA, event.indexB, event.type);
        m_currentAlgorithmWidget->updateVisualization();
    }
}

void MainWindow::onStart() {
    if (!m_engine || m_engine->isFinished()) return;
    m_running = true;
    int ms = 510 - m_speedSlider->value() * 25;
    m_timer->start(ms);
    m_startBtn->setEnabled(false);
    m_pauseBtn->setEnabled(true);
}

void MainWindow::onPause() {
    m_timer->stop();
    m_running = false;
    m_startBtn->setEnabled(true);
    m_pauseBtn->setEnabled(false);
}

void MainWindow::onReset() {
    m_timer->stop();
    m_running = false;
    m_startBtn->setEnabled(true);
    m_pauseBtn->setEnabled(false);
    setupEngine(m_currentCategory, m_currentAlgorithm);
}

void MainWindow::onTimerTick() {
    if (!m_engine->step()) {
        m_timer->stop();       // algorithm finished
        m_startBtn->setEnabled(false);
        m_pauseBtn->setEnabled(false);
    }
}

void MainWindow::onBackToHome() {
    m_timer->stop();
    m_running = false;
    m_startBtn->setEnabled(true);
    m_pauseBtn->setEnabled(false);
    showHomePage();
}

void MainWindow::showHomePage() {
    m_stackedWidget->setCurrentWidget(m_homePage);
    setWindowTitle("Algorithm Visualizer - Home");
}

void MainWindow::showAlgorithmPage() {
    m_stackedWidget->setCurrentWidget(m_algorithmPage);
    setWindowTitle(QString("Algorithm Visualizer - %1: %2").arg(m_currentCategory, m_currentAlgorithm));
}
