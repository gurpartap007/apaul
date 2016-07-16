#include "qlinphone.h"
#include "ui_qlinphone.h"
bool CallOutgoingRinging=false;
bool CallOutgoingEarlyMedia=false;
bool CallConnected=false;
bool CallStreamsRunning=false;
bool CallEnd=false;
bool CallError=false;
bool isIncomingCall= false;
extern char input[3];
qlinphone::qlinphone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qlinphone)
{
    ui->setupUi(this);
    qlinphone_init();
}

qlinphone::~qlinphone()
{
    delete ui;
}

void qlinphone::qlinphone_init()
{
    QDir confDir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
       confDir.mkdir("Linphone");
       QString config_file = confDir.absolutePath() + "/Linphone/.linphonerc";
       LinphoneCoreVTable vtable = {0};
       vtable.call_state_changed = qcall_state_changed;
       lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);
       QTimer *timer = new QTimer();
       connect(timer,SIGNAL(timeout()), this,SLOT(iterate()));
       timer->start(5);
       linphone_core_set_capture_device(lc,linphone_core_get_capture_device(lc));
       qDebug() << linphone_core_get_capture_device(lc);
	
}

int qlinphone::qlinphone_call(LinphoneCore *lc, char *ip_address)
{
    LinphoneCall *call1;
    if ( ! ip_address || ! *ip_address )
       {
           return -1;

       }
       {
           LinphoneCallParams *cp=linphone_core_create_call_params(lc,call1);

           if ( linphone_core_in_call(lc) )
           {
               qDebug() << "Terminate or hold on the current call first.\n";
               return 1;
           }

           if ( NULL == (call=linphone_core_invite_with_params(lc,ip_address,cp)) )
           {
               qDebug() << "Error from linphone_core_invite.\n";
           }
           else
           {
               linphone_call_enable_echo_cancellation(call,true);               
		linphone_call_enable_echo_limiter(call,true);
               qDebug() << "callee name " << ip_address;

           }

           linphone_call_params_destroy(cp);
       }
    return 0;
}

void qlinphone::iterate()
{
    linphone_core_iterate(lc);
        if(CallConnected)
        {
            CallConnected=false;
            emit Call_connected();
            qDebug() << "Current Call Connected";
        }
        else if(CallOutgoingRinging)
        {
            CallOutgoingRinging=false;
            qDebug() << "Call Outgoing Ringing";
        }
        else if(CallOutgoingEarlyMedia)
        {
            CallOutgoingEarlyMedia=false;
            qDebug() << "Call Outgoing to remote";
        }
        else if(CallStreamsRunning)
        {
            CallStreamsRunning=false;
            qDebug() << "Call Streams Running";
        }
        else if(CallEnd)
        {
            CallEnd=false;
            emit Call_ended();
            qDebug() << "Current Call Ended";
        }
        else if(CallError)
        {
            CallError=false;
            qDebug() << "Error in establishing current Call";
        }
        else if(isIncomingCall)
        {
            QStringList caller_id;
            new_call=linphone_core_get_current_call(lc);
            caller_id = QString::fromUtf8(linphone_call_get_remote_address_as_string(new_call)).split('@');
            linphone_core_set_playback_device(lc,linphone_core_get_playback_device(lc));
            linphone_core_play_local(lc,"/opt/linphone/tester/sounds/oldphone.wav");
            isIncomingCall = false;
        }
}

void qlinphone::talk_to_driver()
{
    QString mop_ip_address ;
    QString input_ip;
    mop_ip_address = "root@192.168.0.";
    input_ip = input;
    mop_ip_address = mop_ip_address + input_ip;
    qDebug() << "MOP ADDRESS" << mop_ip_address;
    //linphone_core_accept_call(lc,NULL);
    qDebug() << "inside talk_to_driver slot";
    qlinphone_call(lc,(char *)mop_ip_address.toStdString().c_str());
}

void qlinphone::end_current_call()
{
    linphone_core_terminate_call(lc,call);
   // CallEnd = true;
}
void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{

    switch(cstate){
    case LinphoneCallOutgoingRinging:
       qDebug() << "It is now ringing remotely";
        CallOutgoingRinging=true;
        qDebug() << "CallOutgoingRinging" << CallOutgoingRinging;
        break;
    case LinphoneCallOutgoingEarlyMedia:
        qDebug() << "Receiving some early media";
        CallOutgoingEarlyMedia=true;
        break;
    case LinphoneCallIncoming:
        qDebug() << "New Incoming Call";
        isIncomingCall = true;
        break;
    case LinphoneCallConnected:
        qDebug() << "We are connected ";
        CallConnected=true;
        break;
    case LinphoneCallStreamsRunning:
        qDebug() << "Media streams established ";
        CallStreamsRunning=true;
        break;
    case LinphoneCallEnd:
        qDebug() << "Call is terminated";
        CallEnd=true;
        break;
    case LinphoneCallError:
        qDebug() << "Call failure !";
        CallError=true;
        break;
    default:
        qDebug() << "Unhandled notification " << cstate;
    }
}
