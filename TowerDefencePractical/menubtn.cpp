#include "menubtn.h"
#include <QSoundEffect>

MenuBtn::MenuBtn(QWidget *parent, QString text, int style) : QWidget(parent)
{
    setFixedSize(250, 75);

    //Create the button for the menu items
    outline = new QLabel(this);
    outline->setGeometry(0, 0, width(), height());
    outline->setStyleSheet("border: 1px solid white; border-radius:8pt; background-color: #ddddea;");
    outline->setAttribute(Qt::WA_TransparentForMouseEvents);  // Allows the parent to receive the click
    outline->setText(text);
    switch(style)
    {
    case 0:
        outline->setStyleSheet("QLabel{border: 1px solid white; border-radius:18px; background-color: rgba(55,99,180,50); font-size: 30px; color: white;}");
        outline->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        break;
    case 1:
        outline->setStyleSheet("QLabel{border: 1px solid white; border-radius:8pt; background-color:  rgba(55,99,180,50); font-size: 30px; color: #7387e4;}");
        outline->setFont(QFont("Comic Sans MS", 15));
        outline->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        break;
    default:
        outline->setStyleSheet("QLabel{font-size: 30px; color: white; text-allign:center;}");
        break;
    }

    state = false;

}

void MenuBtn::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //state = !state;
        //play the click sound effect on every button clicked
        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/ClickEffect.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0
        effect->play();
        emit clicked(state);
    }
}

void MenuBtn::setState(bool s)
{
    state = s;
}
