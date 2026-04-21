// src/ui/SortingWidget.h
#pragma once
#include <QWidget>
#include <vector>
#include "engine/AlgorithmEngine.h"
#include <memory>



class SortingWidget : public QWidget {
    Q_OBJECT
 
public:
    explicit SortingWidget(QWidget* parent = nullptr);
 
    void setData(std::shared_ptr<std::vector<int>> data);
    void swapBars(int a, int b);
    void highlight(int a, int b, StepEvent::Type type);
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
