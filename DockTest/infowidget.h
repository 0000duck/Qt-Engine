#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>

namespace Ui
{
class InfoWidget;
}
class GameObject;

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(GameObject* go = nullptr,QWidget *parent = 0);
    ~InfoWidget();

public slots:
    void SetName(QString);
    void SetActive(bool);
    void SetVisible(bool);

signals:
    void InspectorUpdate();

private:
    Ui::InfoWidget *ui;
    GameObject* go = nullptr;
};

#endif // INFOWIDGET_H
