// src/ui/MainWindow.cpp
#include "ui/MainWindow.h"
#include "ui/SortingWidget.h"
#include "engine/BubbleSortEngine.h"


static const char* TAG = "MainWindow";

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Algorithm Visualizer");
    resize(900, 600);

    auto* central = new QWidget(this);
    setCentralWidget(central);

    auto* mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    // Visualization area
    m_sortWidget = new SortingWidget(this);
    mainLayout->addWidget(m_sortWidget, 1);

    // Controls bar
    auto* controls = new QHBoxLayout();

    m_startBtn  = new QPushButton("Start",  this);
    m_pauseBtn  = new QPushButton("Pause",  this);
    m_resetBtn  = new QPushButton("Reset",  this);
    m_pauseBtn->setEnabled(false);

    auto* speedLabel = new QLabel("Speed:", this);
    m_speedSlider = new QSlider(Qt::Horizontal, this);
    m_speedSlider->setRange(1, 20);   // 1 = slow (500ms), 20 = fast (10ms)
    m_speedSlider->setValue(10);
    m_speedSlider->setFixedWidth(150);

    controls->addWidget(m_startBtn);
    controls->addWidget(m_pauseBtn);
    controls->addWidget(m_resetBtn);
    controls->addStretch();
    controls->addWidget(speedLabel);
    controls->addWidget(m_speedSlider);

    mainLayout->addLayout(controls);

    // Timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    // Buttons
    connect(m_startBtn,  &QPushButton::clicked, this, &MainWindow::onStart);
    connect(m_pauseBtn,  &QPushButton::clicked, this, &MainWindow::onPause);
    connect(m_resetBtn,  &QPushButton::clicked, this, &MainWindow::onReset);

    // Speed slider updates timer interval live
    connect(m_speedSlider, &QSlider::valueChanged, this, [this](int val) {
        int ms = 510 - val * 25;   // val=1 → 485ms, val=20 → 10ms
        m_timer->setInterval(ms);
    });

    setupEngine();
}

void MainWindow::setupEngine() {
    auto engine = std::make_unique<BubbleSortEngine>();
    auto data = std::make_shared<std::vector<int>>(
        std::vector<int>{64, 34, 25, 12, 22, 11, 90, 45, 77, 55}
    );
    engine->initialize(data);

    // Wire the callback: engine fires → UI repaints
    engine->setStepCallback([this](const StepEvent& e) {
        LOG_DEBUG(TAG, "Received event: " + std::to_string(static_cast<int>(e.type)) +
                         " indices: " + std::to_string(e.indexA) + ", " + std::to_string(e.indexB));
        applyStep(e);
    });

    m_engine = std::move(engine);
    m_sortWidget->setData(data);
}

void MainWindow::applyStep(const StepEvent& event) {
    LOG_DEBUG(TAG, "Applying step: " + std::to_string(static_cast<int>(event.type)) +
                     " indices: " + std::to_string(event.indexA) + ", " + std::to_string(event.indexB));
    m_sortWidget->highlight(event.indexA, event.indexB, event.type);
    m_sortWidget->update();   // triggers repaint
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
    setupEngine();
}

void MainWindow::onTimerTick() {
    
    if (!m_engine->step()) {
        m_timer->stop();       // algorithm finished
        m_startBtn->setEnabled(false);
        m_pauseBtn->setEnabled(false);
    }
}
