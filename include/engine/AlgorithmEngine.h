#pragma once
#include <functional>
#include <vector>
#include <memory>

struct StepEvent {
    enum class Type { Compare, Swap, Visit, PathFound, Done };
    Type type;
    int indexA = -1;
    int indexB = -1;
};

class AlgorithmEngine {
public:
    virtual ~AlgorithmEngine() = default;

    virtual void initialize(std::shared_ptr<std::vector<int>>  data) = 0;

    bool step() {
        if (m_finished) return false;
        return doStep();
    }

    void setStepCallback(std::function<void(const StepEvent&)> cb) {
        m_callback = std::move(cb);
    }

    bool isFinished() const { return m_finished; }

protected:
    virtual bool doStep() = 0;

    void fireEvent(const StepEvent& event) {
        if (m_callback) m_callback(event);
    }

    bool m_finished = false;

private:
    std::function<void(const StepEvent&)> m_callback;
};