#ifndef DB_HTTPINTERFACE_H
#define DB_HTTPINTERFACE_H

#include <QObject>
#include <QtNetwork>
class QNetworkReply;
class QNetworkAccessManager;

struct HttpResultData{
    HttpResultData() {
        state = -1;
    }
    int state;
    QString telephone;
    int id;
    QString code;
    QString url;
    QString uuid;
    QVector<QVariant> dataList;
};

// http返回消息
typedef struct NewHttpResultData {
    NewHttpResultData () { state = -1; }
    int state;          //状态 ,1代表成功
    QString code;       //提示信息
    QVariant variant;   //扩展(各种消息体)
}_HttpRetData;
Q_DECLARE_METATYPE(_HttpRetData)   //QVariant可识别

// 版本更新消息体
typedef struct CheckUpdateData {
    QString version;        //版本号
    QString downloadUrl;    //下载网址
    QString fileName;       //文件名
    QString fileStyle;      //文件格式
}_CheUpdaData;
Q_DECLARE_METATYPE(_CheUpdaData)

//课件信息消息体
typedef struct CoursewareInfoData {
    QString createTime;       //创建时间
    QString fileName;         //文件名
    QString fileType;         //文件类型
    QString fileSavePath;     //url存储路径
    int fileId;               //文件ID
    int subjectId;            //用户ID
    int fileSize;             //文件大小
    int whiteRelateId;        //用户关联表ID
}_CoIoData;
Q_DECLARE_METATYPE(_CoIoData)

//分享链接消息体
typedef struct SharingLinkData {
    QString code;       //链接
    QString password;   //密码
}_ShaLinkData;
Q_DECLARE_METATYPE(_ShaLinkData)

//用户信息消息体
typedef struct UserInformationData {
    QString telephone;      //手机号
    QString loginType;      //绑定账号类型（微信）
    QString loginTypeName;  //绑定账号名称（微信名）
    QString roleName;       //角色
    QString userIconPath;   //用户头像
    QString userName;       //用户名称
    int userId;             //用户id
}_UserInfoData;
Q_DECLARE_METATYPE(_UserInfoData)

//二维码消息体
typedef struct QrCodeData {
    QString url;
    QString uuid;
}_QrCoData;
Q_DECLARE_METATYPE(_QrCoData)

//用户头像数据
typedef struct UserIconData {
    QByteArray data;
}_UsrIcoData;
Q_DECLARE_METATYPE(_UsrIcoData)

//http功能
enum HttpFunction {
    CheckUpdate,            //检查更新
    DownloadFile,           //下载文件
    CheckRegistered,        //检查是否已经注册
    GetCoursewareInfo,      //获取课件信息
    UploadCourseware,       //上传课件
    GenerateLink,           //生成分享链接
    GetVerificationCode,    //发送验证码
    CheckVerificationCode,  //校验验证码
    RegisterAccount,        //注册账号
    LoginAccount,           //登录账号
    GetQrCode,              //获取二维码
    QrCodeLogin,            //二维码登录
    CancelQrCodeLogin,      //取消二维码登录
    GetUserIconData,        //获取用户头像数据
    Cancellation,           //注销
    UnBind,                 //解绑
    MobileSharing           //手机分享

};


class DB_HttpInterface : public QObject
{
    Q_OBJECT
public:
    DB_HttpInterface();
    static DB_HttpInterface* getInstace();
    // http请求
    _HttpRetData httpRequest(HttpFunction fun, QStringList args, QVariant variant = QVariant());
    void downloadUpdatePackageRequest(QString m_pUrl, QString m_pFilePath);

private:
    //处理返回消息
    void processingRetMessages(HttpFunction fun, QJsonObject *jsonObject, _HttpRetData* data);

private slots:
    void readReplyData();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QString m_pSaveFilePath;
    QNetworkReply *m_pNetworkReply;
    QEventLoop *_loop;

signals:
    //void downloadFileResult(QByteArray bytes);
    void downloadProgress(qint64, qint64);
    void downloadFileFinished();
};

#endif // DB_HTTPINTERFACE_H
