#include "menubtn.h"
#include <QSoundEffect>

MenuBtn::MenuBtn(QWidget *parent) : QWidget(parent)
{
    setFixedSize(250, 75);

    outline = new QLabel(this);
    outline->setGeometry(0, 0, width(), height());
    outline->setStyleSheet("border: 1px solid white; background-color: rgba(0, 0, 0, 0);");
    outline->setAttribute(Qt::WA_TransparentForMouseEvents);  // Allows the parent to receive the click
    state = true;

}

void MenuBtn::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        state = !state;
        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/ClickEffect.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0
        effect->play();
        emit clicked(state);
    }
}
