// src/engine/BubbleSortEngine.cpp
#include "engine/BubbleSortEngine.h"
#include <algorithm>
#include "utils/Logger.h"
#include <memory>

static const char* TAG = "BubbleSortingEngine";

void BubbleSortEngine::initialize(std::shared_ptr<std::vector<int>> data) {
    m_data = data;
    m_i = 0;
    m_j = 0;
    m_finished = false;
}

bool BubbleSortEngine::doStep() {
    int n = static_cast<int>(m_data->size());
    if (m_i >= n - 1) { m_finished = true; return false; }

    // fireEvent a comparison event so the UI can highlight these two bars
    fireEvent({ StepEvent::Type::Compare, m_j, m_j + 1 });

    if (m_data->at(m_j) > m_data->at(m_j + 1)) {
        std::swap(m_data->at(m_j), m_data->at(m_j + 1));
        fireEvent({ StepEvent::Type::Swap, m_j, m_j + 1 });
    }

    m_j++;
    if (m_j >= n - 1 - m_i) {
        m_j = 0;
        m_i++;
    }
    return true;
}
