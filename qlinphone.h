#ifndef QLINPHONE_H
#define QLINPHONE_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QStandardPaths>
#include <QTimer>
#include <QFileInfo>
#include <QDir>
#include "linphone/linphonecore.h"
void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);
namespace Ui {
class qlinphone;
}

class qlinphone : public QWidget
{
    Q_OBJECT

public:
    explicit qlinphone(QWidget *parent = 0);
    LinphoneCore       *lc;
    LinphoneCall       *call2;
    const MSList       *call_logs;
    LinphoneCall *call,*incoming_call,*new_call;
    ~qlinphone();
signals:
    void Call_ended();
    void Call_connected();
public slots:
    void qlinphone_init();
    int qlinphone_call(LinphoneCore *lc, char *ip_address);
    void iterate();
    void talk_to_driver();
    void end_current_call();
private:
    Ui::qlinphone *ui;
    friend void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);
};

#endif // QLINPHONE_H
