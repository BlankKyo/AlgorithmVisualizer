// src/ui/HomePage.cpp
#include "ui/HomePage.h"
#include "utils/MemoryUtils.h"
#include "utils/Logger.h"
#include <QFont>
#include <QPalette>

static const char* TAG = "HomePage";

HomePage::HomePage(QWidget* parent) : QWidget(parent) {
    setupUI();
    LOG_DEBUG(TAG, MemoryUtils::formatLifecycleLog("Constructor", this, sizeof(*this)));
}

HomePage::~HomePage() {
    LOG_DEBUG(TAG, MemoryUtils::formatLifecycleLog("Destructor", this, sizeof(*this)));
}



void HomePage::setupUI() {
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(15);

    // Title
    m_titleLabel = new QLabel("Algorithm Visualizer", this);
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(m_titleLabel);

    // Subtitle
    QLabel* subtitle = new QLabel("Choose an algorithm category and select an algorithm to visualize", this);
    subtitle->setAlignment(Qt::AlignCenter);
    QFont subtitleFont = subtitle->font();
    subtitleFont.setPointSize(12);
    subtitle->setFont(subtitleFont);
    m_mainLayout->addWidget(subtitle);

    // Content area
    m_contentLayout = new QHBoxLayout();
    m_contentLayout->setSpacing(20);

    // Categories section
    QGroupBox* categoryGroup = new QGroupBox("Categories", this);
    QVBoxLayout* categoryLayout = new QVBoxLayout(categoryGroup);

    m_categoryList = new QListWidget(this);
    m_categoryList->addItem("Sorting");
    m_categoryList->addItem("Searching");
    m_categoryList->addItem("Graph Algorithms");
    m_categoryList->addItem("Dynamic Programming");
    m_categoryList->setCurrentRow(0); // Select sorting by default

    categoryLayout->addWidget(m_categoryList);
    m_contentLayout->addWidget(categoryGroup);

    // Algorithms section
    QGroupBox* algorithmGroup = new QGroupBox("Algorithms", this);
    QVBoxLayout* algorithmLayout = new QVBoxLayout(algorithmGroup);

    m_algorithmList = new QListWidget(this);
    populateAlgorithms("Sorting");

    algorithmLayout->addWidget(m_algorithmList);
    m_contentLayout->addWidget(algorithmGroup);

    // Description section
    QGroupBox* descriptionGroup = new QGroupBox("Description", this);
    QVBoxLayout* descriptionLayout = new QVBoxLayout(descriptionGroup);

    m_descriptionLabel = new QLabel(this);
    m_descriptionLabel->setWordWrap(true);
    m_descriptionLabel->setMinimumHeight(100);
    descriptionLayout->addWidget(m_descriptionLabel);

    m_contentLayout->addWidget(descriptionGroup);

    m_mainLayout->addLayout(m_contentLayout);

    // Connect signals
    connect(m_categoryList, &QListWidget::currentTextChanged,
            this, &HomePage::onCategoryChanged);
    connect(m_algorithmList, &QListWidget::itemDoubleClicked,
            this, &HomePage::onAlgorithmDoubleClicked);

    // Set initial description
    onCategoryChanged();
}

void HomePage::onCategoryChanged() {
    QString category = m_categoryList->currentItem()->text();
    populateAlgorithms(category);

    // Update description based on category
    if (category == "Sorting") {
        m_descriptionLabel->setText("Sorting algorithms arrange elements in a specific order. "
                                  "Watch as different algorithms compare and swap elements to achieve order.");
    } else if (category == "Searching") {
        m_descriptionLabel->setText("Searching algorithms find specific elements within data structures. "
                                  "Visualize how different search techniques locate target values.");
    } else if (category == "Graph Algorithms") {
        m_descriptionLabel->setText("Graph algorithms work with nodes and edges. "
                                  "Explore pathfinding, traversal, and optimization algorithms on graph structures.");
    } else if (category == "Dynamic Programming") {
        m_descriptionLabel->setText("Dynamic programming solves complex problems by breaking them down into simpler subproblems. "
                                  "See how optimal solutions are built step by step.");
    }
}

void HomePage::populateAlgorithms(const QString& category) {
    m_algorithmList->clear();

    if (category == "Sorting") {
        m_algorithmList->addItem("Bubble Sort");
        m_algorithmList->addItem("Quick Sort");
        m_algorithmList->addItem("Merge Sort");
        m_algorithmList->addItem("Insertion Sort");
        m_algorithmList->addItem("Selection Sort");
    } else if (category == "Searching") {
        m_algorithmList->addItem("Linear Search");
        m_algorithmList->addItem("Binary Search");
    } else if (category == "Graph Algorithms") {
        m_algorithmList->addItem("Breadth-First Search");
        m_algorithmList->addItem("Depth-First Search");
        m_algorithmList->addItem("Dijkstra's Algorithm");
        m_algorithmList->addItem("A* Search");
    } else if (category == "Dynamic Programming") {
        m_algorithmList->addItem("Fibonacci Sequence");
        m_algorithmList->addItem("Knapsack Problem");
        m_algorithmList->addItem("Longest Common Subsequence");
    }
}

void HomePage::onAlgorithmDoubleClicked(QListWidgetItem* item) {
    QString category = m_categoryList->currentItem()->text();
    QString algorithm = item->text();
    emit algorithmSelected(category, algorithm);
}