#include "QtConsole.h"
#include "ui_QtConsole.h"
#include "System.h"

QtConsole::QtConsole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtConsole)
{
    ui->setupUi(this);
    Console::Instance = this;
}

QtConsole::~QtConsole()
{
    delete ui;
}

void QtConsole::Print(const tjs_char *msg)
{
    if(DE::System::GetInstance()->getDebugMode() > 0){
        show();
    }
    else {
        return;
    }
//    QTextCursor cursor = ui->textEdit->textCursor();
//    cursor.movePosition( QTextCursor::StartOfLine );//行首
//    cursor.movePosition( QTextCursor::Right, QTextCursor::MoveAnchor, 0);//向右移动到Pos
//    cursor.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
//    ui->textEdit->setTextCursor( cursor ); // added
//    QTextCharFormat defcharfmt = ui->textEdit->currentCharFormat();
//    QTextCharFormat newcharfmt = defcharfmt;
//    newcharfmt.setFontUnderline( true );
//    newcharfmt.setUnderlineColor( QColor( Qt::red ) );
//    newcharfmt.setUnderlineStyle( QTextCharFormat::SingleUnderline );
//    ui->textEdit->setCurrentCharFormat( newcharfmt );
    
//    cursor.movePosition( QTextCursor::PreviousCharacter );//加上这句是为了去除光标selected
//    ui->textEdit->setTextCursor( cursor ); // added
//    // ui->view1->setCurrentCharFormat( defcharfmt );
//    ui->textEdit->setFocus();
    ui->textEdit->append(DE::String(msg).c_nstr());
}
