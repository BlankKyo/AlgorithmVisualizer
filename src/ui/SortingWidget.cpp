// src/ui/SortingWidget.cpp
#include "ui/SortingWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include "utils/Logger.h"
#include "utils/MemoryUtils.h"
#include <memory>

static const char* TAG = "SortingWidget";

SortingWidget::SortingWidget(QWidget* parent) : AlgorithmWidget(parent) {
    setMinimumHeight(300);
    setStyleSheet("background-color: #1e1e2e;");
    LOG_DEBUG(TAG, MemoryUtils::formatLifecycleLog("Constructor", this, sizeof(*this)));
}

SortingWidget::~SortingWidget() {
    LOG_DEBUG(TAG, MemoryUtils::formatLifecycleLog("Destructor", this, sizeof(*this)));
}

void SortingWidget::setData(std::shared_ptr<std::vector<int>> data) {
    m_data = data;
    m_highlightA = m_highlightB = -1;
    update();
}

void SortingWidget::highlight(int a, int b, StepEvent::Type type) {
    m_highlightA = a;
    m_highlightB = b;
    m_lastType   = type;
}

void SortingWidget::updateVisualization() {
    update();
}

void SortingWidget::paintEvent(QPaintEvent*) {
    if (m_data->empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int W     = width();
    const int H     = height();
    const int n     = static_cast<int>(m_data->size());
    const int gap   = 4;
    const int barW  = (W - gap * (n + 1)) / n;
    const int maxVal = *std::max_element(m_data->begin(), m_data->end());

    for (int i = 0; i < n; ++i) {
        int barH = static_cast<int>((static_cast<double>(m_data->at(i)) / maxVal) * (H - 20));
        int x    = gap + i * (barW + gap);
        int y    = H - barH;

        QColor color = QColor("#4a90d9");  // default blue
        if (i == m_highlightA || i == m_highlightB) {
            color = (m_lastType == StepEvent::Type::Swap)
                ? QColor("#e05c5c")   // red for swap
                : QColor("#f5c842");  // yellow for comparison
        }

        painter.fillRect(x, y, barW, barH, color);
    }
}
