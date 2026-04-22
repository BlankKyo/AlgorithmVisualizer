// src/ui/AlgorithmWidget.cpp
#include "ui/AlgorithmWidget.h"

static const char* TAG = "AlgorithmWidget";


AlgorithmWidget::AlgorithmWidget(QWidget* parent) : QWidget(parent) {
}

void AlgorithmWidget::setEngine(std::unique_ptr<AlgorithmEngine> engine) {
    m_engine = std::move(engine);
}