#pragma once
#include "AlgorithmEngine.h"
#include <memory>

class BubbleSortEngine : public AlgorithmEngine {
public:
    void initialize(std::shared_ptr<std::vector<int>>  data) override;

protected:
    bool doStep() override;

private:
    std::shared_ptr<std::vector<int>> m_data;
    int m_i = 0;
    int m_j = 0;
};