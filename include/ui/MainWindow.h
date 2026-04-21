// src/ui/MainWindow.h
#pragma once
#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "engine/AlgorithmEngine.h"
#include "ui/SortingWidget.h"
#include "utils/Logger.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>


class MainWindow : public QMainWindow {
    Q_OBJECT
 
public:
    explicit MainWindow(QWidget* parent = nullptr);
 
private slots:
    void onStart();
    void onPause();
    void onReset();
    void onTimerTick();
 
private:
    void setupEngine();
    void applyStep(const StepEvent& event);
 
    SortingWidget*                   m_sortWidget  = nullptr;
    QPushButton*                     m_startBtn    = nullptr;
    QPushButton*                     m_pauseBtn    = nullptr;
    QPushButton*                     m_resetBtn    = nullptr;
    QSlider*                         m_speedSlider = nullptr;
    QLabel*                          m_statusLabel = nullptr;
    QTimer*                          m_timer       = nullptr;
    std::unique_ptr<AlgorithmEngine> m_engine;
    bool                             m_running     = false;
};
