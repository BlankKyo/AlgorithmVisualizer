// src/ui/SortingWidget.h
#pragma once
#include "ui/AlgorithmWidget.h"
#include <vector>
#include <memory>



class SortingWidget : public AlgorithmWidget {
    Q_OBJECT

public:
    explicit SortingWidget(QWidget* parent = nullptr);

    ~SortingWidget();

    void setData(std::shared_ptr<std::vector<int>> data) override;
    void highlight(int indexA, int indexB, StepEvent::Type type) override;
    void updateVisualization() override;
    void swapBars(int a, int b);
    void markSorted(int fromIndex);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<std::vector<int>> m_data = nullptr;
    int               m_highlightA  = -1;
    int               m_highlightB  = -1;
    int               m_sortedFrom  = -1;
    StepEvent::Type   m_lastType    = StepEvent::Type::Done;
};
