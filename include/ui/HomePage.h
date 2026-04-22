// include/ui/HomePage.h
#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QGroupBox>

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget* parent = nullptr);

    ~HomePage();

signals:
    void algorithmSelected(const QString& category, const QString& algorithm);

private slots:
    void onCategoryChanged();
    void onAlgorithmDoubleClicked(QListWidgetItem* item);

private:
    void setupUI();
    void populateAlgorithms(const QString& category);

    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_contentLayout;

    QListWidget* m_categoryList;
    QListWidget* m_algorithmList;

    QLabel* m_titleLabel;
    QLabel* m_descriptionLabel;
};