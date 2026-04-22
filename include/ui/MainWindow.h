// src/ui/MainWindow.h
#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QStackedWidget>
#include <memory>
#include "engine/AlgorithmEngine.h"
#include "ui/AlgorithmWidget.h"
#include "ui/HomePage.h"
#include "utils/Logger.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QAction>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

private slots:
    void onStart();
    void onPause();
    void onReset();
    void onTimerTick();
    void onAlgorithmSelected(const QString& category, const QString& algorithm);
    void onBackToHome();

private:
    void setupUI();
    void setupEngine(const QString& category, const QString& algorithm);
    void applyStep(const StepEvent& event);
    void showHomePage();
    void showAlgorithmPage();

    QStackedWidget* m_stackedWidget;
    HomePage* m_homePage;
    QWidget* m_algorithmPage;
    AlgorithmWidget* m_currentAlgorithmWidget;

    // Controls
    QPushButton* m_startBtn;
    QPushButton* m_pauseBtn;
    QPushButton* m_resetBtn;
    QPushButton* m_backBtn;
    QSlider* m_speedSlider;
    QLabel* m_statusLabel;
    QTimer* m_timer;

    std::unique_ptr<AlgorithmEngine> m_engine;
    bool m_running = false;

    QString m_currentCategory;
    QString m_currentAlgorithm;
};
