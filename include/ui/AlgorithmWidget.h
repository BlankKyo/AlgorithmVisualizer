// include/ui/AlgorithmWidget.h
#pragma once
#include <QWidget>
#include <memory>
#include "engine/AlgorithmEngine.h"

class AlgorithmWidget : public QWidget {
    Q_OBJECT

public:
    explicit AlgorithmWidget(QWidget* parent = nullptr);
    virtual ~AlgorithmWidget() = default;

    virtual void setData(std::shared_ptr<std::vector<int>> data) = 0;
    virtual void highlight(int indexA, int indexB, StepEvent::Type type) = 0;
    virtual void updateVisualization() = 0;

    void setEngine(std::unique_ptr<AlgorithmEngine> engine);
    AlgorithmEngine* getEngine() const { return m_engine.get(); }

protected:
    std::unique_ptr<AlgorithmEngine> m_engine;
};