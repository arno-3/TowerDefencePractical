#ifndef JUST_TO_TEST_QT_FRAMEWORK_INHERITANCE_H
#define JUST_TO_TEST_QT_FRAMEWORK_INHERITANCE_H

#include <QObject>
#include <QWidget>

class just_to_test_qt_framework_inheritance : public QObject
{
    Q_OBJECT
public:
    explicit just_to_test_qt_framework_inheritance(QObject *parent = nullptr);

signals:

};

#endif // JUST_TO_TEST_QT_FRAMEWORK_INHERITANCE_H
