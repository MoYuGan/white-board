#include "db_httpinterface.h"

#include <QDateTime>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonObject>
#include <QEventLoop>
#include <QUrl>
#include <QIODevice>

#define HTTP_HOST "https://test-yunkec.amdox.com.cn"
//#define HTTP_HOST "https://test-yunke.amdox.com.cn"
//#define HTTP_HOST "http://192.168.5.26:13980"
//#define HTTP_HOST "http://192.168.5.113:13980"

DB_HttpInterface::DB_HttpInterface()
{
}

DB_HttpInterface* DB_HttpInterface::getInstace()
{
    static DB_HttpInterface* sHttpInterface = nullptr;
    if(!sHttpInterface)
    {
        sHttpInterface = new DB_HttpInterface;
    }
    return sHttpInterface;
}

/*
*参数:
*   fun:请求类型（功能）
*   args:参数
*   variant:拓展
*/
_HttpRetData DB_HttpInterface::httpRequest(HttpFunction fun, QStringList args, QVariant variant)
{
    Q_UNUSED(variant)
    QEventLoop _loop;
    QTimer _timer;
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, &_loop, &QEventLoop::quit);
    connect(&_timer, &QTimer::timeout, &_loop,&QEventLoop::quit);

    QUrlQuery query;
    QUrl url;
    QHttpMultiPart *multiPart;
    QNetworkRequest request;
    QNetworkReply *reply;
    _HttpRetData data;

    //发送请求
    switch(fun) {
    case HttpFunction::CheckUpdate: {   //检查更新
        url.setUrl(QString("https://version.amdox.com.cn/version/linux/whiteBoard/getLatestVersion?versionCode=100000"));
        request.setUrl(url);
        request.setHeader(QNetworkRequest::UserAgentHeader,"RT-Thread ART");
        reply = manager->get(request);
    }break;

    case HttpFunction::GetCoursewareInfo:{    //获取课件信息
        if (args.size() != 3)
            return data;
        query.addQueryItem("userId", args.at(0));       //用户Id
        query.addQueryItem("subjectType", args.at(1));  //用户类型 0=白板用户 1=教师
        query.addQueryItem("dataSort", args.at(2));     //是否倒序,1代表是,0代表否
        url.setUrl(QString("%1/cloudClass/web/whiteWare/selectWhiteWareByPage/0/0").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::UploadCourseware: {    //上传课件
        if (args.size() != 3)
            return data;
        QFileInfo fileInfo(args.at(2));
        QFile file(args.at(2));
        if (!file.open(QIODevice::ReadOnly)) {
            return data;
        }

        multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart dataPart;
        dataPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
        dataPart.setHeader(QNetworkRequest::ContentDispositionHeader
           ,QVariant(QString("form-data; name=\"wareFiles\";filename=\"%1\"").arg(fileInfo.fileName())));
        dataPart.setBody(file.readAll());
        multiPart->append(dataPart);
        file.close();

        query.addQueryItem("id", args.at(0));           //用户Id
        query.addQueryItem("roleName", args.at(1));     //用户类型 0=白板用户 1=教师
        url.setUrl(QString("%1/cloudClass/web/whiteWare/uploadWare?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply  = manager->post(request, multiPart);
    }break;

    case HttpFunction::GenerateLink: {   //生成分享链接
        if (args.size() != 3)
            return data;
        query.addQueryItem("fileId", args.at(0));           //用户关联表ID
        query.addQueryItem("algorithmType", args.at(1));    //是否加密,1代表否, 2代表是
        query.addQueryItem("timeScope", args.at(2));       //过期时间,1代表一天,2代表一周,3代表一月
        url.setUrl(QString("%1/cloudClass/web/whiteWare/share/genorenceLink?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        reply = manager->post(request, "");
    }break;

    case HttpFunction::DownloadFile: {  //下载文件
        if (args.size() != 2)
            return data;
        m_pSaveFilePath = args.at(1);   //存储文件
        url.setUrl(args.at(0));         //下载网址
        request.setUrl(url);
        //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        m_pNetworkReply = manager->get(request);
        //写入文件
        connect(m_pNetworkReply, &QNetworkReply::readyRead, this, &DB_HttpInterface::readReplyData, Qt::DirectConnection);
        //下载进度
        connect(m_pNetworkReply, &QNetworkReply::downloadProgress, this, &DB_HttpInterface::onDownloadProgress, Qt::DirectConnection);  
    }break;

    case HttpFunction::CheckRegistered: {   //检查是否已经注册
        if (args.size() != 1)
            return data;
        query.addQueryItem("telephone", args.at(0));    //手机号
        url.setUrl(QString("%1/cloudClass/web/whiteWare/phoneIfExist?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::GetVerificationCode: {   //发送验证码
        if (args.size() != 1)
            return data;
        query.addQueryItem("telephone", args.at(0));    //手机号
        url.setUrl(QString("%1/cloudClass/web/whiteWare/getCode?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::CheckVerificationCode: {     //校验验证码
        if (args.size() != 2)
            return data;
        query.addQueryItem("telephone", args.at(0));    //手机号
        query.addQueryItem("code", args.at(1));         //验证码
        url.setUrl(QString("%1/cloudClass/web/whiteWare/checkCodeValid?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::RegisterAccount: {   //注册账号
        if (args.size() != 3)
            return data;
        query.addQueryItem("code", args.at(0));         //验证码
        query.addQueryItem("password", args.at(1));     //密码
        query.addQueryItem("telephone", args.at(2));    //手机号
        url.setUrl(QString("%1/cloudClass/web/whiteWare/register?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        reply= manager->post(request,"");
    }break;

    case HttpFunction::LoginAccount: {  //登录账号
        if (args.size() != 3)
            return data;
        query.addQueryItem("loginType", args.at(0));
        query.addQueryItem("password", args.at(1));
        query.addQueryItem("telephone", args.at(2));
        url.setUrl(QString("%1/cloudClass/web/whiteWare/doLogin?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setUrl(url);
        reply = manager->post(request, "");
    }break;

    case HttpFunction::GetQrCode: {     //获取二维码
        if (args.size() != 1)
            return data;
        query.addQueryItem("authService", args[0]);
        url.setUrl(QString("%1/cloudClass/web/whiteWare/tempAddSmarkQrCode?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::QrCodeLogin: {    //二维码登录
        if (args.size() != 2)
            return data;
        query.addQueryItem("loginType", args[0]);
        query.addQueryItem("uuid", args[1]);
        url.setUrl(QString("%1/cloudClass/web/whiteWare/pcQrCodeLoginState?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::CancelQrCodeLogin: { //取消二维码登录
        if (args.size() != 1)
            return data;
        query.addQueryItem("uuid", args[0]);
        url.setUrl(QString("%1/cloudClass/web/whiteWare/cancelCodeLogin?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::GetUserIconData: {   //获取用户头像数据
        if (args.size() != 1)
            return data;
        url.setUrl(args.at(0));         //下载网址
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::Cancellation: {  //注销
            return data;
    }break;

    case HttpFunction::UnBind: {    //解绑
        if (args.size() != 1)
            return data;
        query.addQueryItem("telephone", args[0]);
        url.setUrl(QString("%1/cloudClass/web/whiteWare/unbindingWhiteBoardUser?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply = manager->get(request);
    }break;

    case HttpFunction::MobileSharing: { //手机分享
        if (args.size() != 2)
            return data;
        query.addQueryItem("fileId", args.at(0));      //文件ID
        query.addQueryItem("telephone", args.at(1));    //手机号
        url.setUrl(QString("%1/cloudClass/web/whiteWare/phoneShare?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        reply = manager->post(request, "");
    }break;

    case HttpFunction::ChangePassword: {   //更改密码
        if (args.size() != 3)
            return data;
        query.addQueryItem("code", args.at(0));         //验证码
        query.addQueryItem("password", args.at(1));     //密码
        query.addQueryItem("telephone", args.at(2));    //手机号
        url.setUrl(QString("%1/cloudClass/web/whiteWare/editPassword?").arg(HTTP_HOST));
        url.setQuery(query);
        request.setUrl(url);
        reply= manager->get(request);
    }break;

    default: {
        manager->deleteLater();
        return data;
    }
    }
    // 设置超时时间
    _timer.start(10000);
    // 阻塞
    _loop.exec();
    if (fun == HttpFunction::DownloadFile) {
        _timer.stop();
    }else if (_timer.isActive()) {
        _timer.stop();
        //处理返回消息
        QByteArray bytes = reply->readAll();
        if (HttpFunction::GetUserIconData == fun) {
            if (!bytes.isEmpty()) {
                data.state = 1;
                _UsrIcoData icoData;
                icoData.data = bytes;
                data.variant = QVariant::fromValue(icoData);
            }else {
                data.state = -1;
            }
        }else {
            QJsonParseError jsonError;
            QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
            if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
            {
                QJsonObject object = doucment.object();
                processingRetMessages(fun, &object, &data); 
            }
        }
    }else {}    //超时

    //释放资源
    if (fun == HttpFunction::DownloadFile) {
        emit this->downloadFileFinished();
        m_pNetworkReply->abort();
    }else {
        reply->abort();
    }
    manager->deleteLater();
    if (HttpFunction::UploadCourseware == fun)
        multiPart->deleteLater();
    return data;
}

//处理返回消息
void DB_HttpInterface::processingRetMessages(HttpFunction fun, QJsonObject *jsonObject, _HttpRetData *data)
{
    //状态,返回数据为空是，toInt()是-1
    data->state = jsonObject->value("state").toString().toInt();
    //提示信息
    data->code = jsonObject->value("code").toString();
    //获取消息体
    switch(fun) {
    case HttpFunction::CheckUpdate: {
        if (1 == data->state) {
            _CheUpdaData cuData;
            cuData.version = jsonObject->value("versionCode").toString();
            cuData.downloadUrl = jsonObject->value("downloadUrl").toString();
            cuData.fileName = jsonObject->value("fileName").toString();
            data->variant = QVariant::fromValue(cuData);
        }
    }break;

    case HttpFunction::GetCoursewareInfo:{
        QVector<_CoIoData> vector;
        QJsonArray array = jsonObject->value("data").toObject().value("list").toArray();
        for (int row = 0; row < array.size(); row++) {
            QJsonObject obj = array[row].toObject();
            _CoIoData coioData;
            coioData.createTime = obj.value("createTime").toString();
            coioData.fileName = obj.value("fileNameNew").toString();
            coioData.fileType = obj.value("whiteCourseWare").toObject().value("fileType").toString();
            coioData.fileSavePath = obj.value("whiteCourseWare").toObject().value("fileSavePath").toString();
            coioData.fileId = obj.value("fileId").toInt();
            coioData.fileSize = obj.value("whiteCourseWare").toObject().value("fileSize").toInt();
            coioData.subjectId = obj.value("subjectId").toInt();
            coioData.whiteRelateId = obj.value("whiteRelateId").toInt();
            vector.push_back(coioData);
        }
        data->variant = QVariant::fromValue(vector);
    }break;

    case HttpFunction::GenerateLink: {
        _ShaLinkData linkData;
        linkData.code = jsonObject->value("data").toObject().value("code").toString();
        linkData.password = jsonObject->value("data").toObject().value("password").toString();
        data->variant = QVariant::fromValue(linkData);
    }break;

    case HttpFunction::QrCodeLogin:{
        qDebug()<< " 122 " << jsonObject->value("data").toObject().value("codeStateEnum").toString() <<Qt::endl;
        qDebug()<< " 121 " << jsonObject->value("state").toString() <<Qt::endl;
         if(jsonObject->value("state").toString() =="2")//失败
         {
            data->state =2;
         }
         else if(jsonObject->value("state").toString() =="2001")//未扫码
         {
            data->state =3;
         }
         else if(jsonObject->value("state").toString() =="2002")//扫码
         {
            data->state =4;
         }
         else if(jsonObject->value("state").toString()=="2003")//取消
         {
            data->state =5;
         }
         else if(jsonObject->value("state").toString() =="2004")// 二维码过期
         {
            data->state =6;
         }
         else if(jsonObject->value("state").toString() =="2005")//用户不存在
         {
            data->state =7;
         }
         else if(jsonObject->value("state").toString() =="2006")//用户未绑定
         {
            data->state =8;
         }
         else if(jsonObject->value("state").toString() == "1")
         {
             data->state =1;
            _UserInfoData userData;
            userData.telephone = jsonObject->value("data").toObject().value("sessionUser").toObject().value("telephone").toString();
            userData.loginType = jsonObject->value("data").toObject().value("sessionUser").toObject().value("loginTye").toString();
            userData.loginTypeName = jsonObject->value("data").toObject().value("sessionUser").toObject().value("loginTypeName").toString();
            userData.roleName = jsonObject->value("data").toObject().value("sessionUser").toObject().value("roleName").toString();
            userData.userIconPath = jsonObject->value("data").toObject().value("sessionUser").toObject().value("userIconPath").toString();
            userData.userName = jsonObject->value("data").toObject().value("sessionUser").toObject().value("userName").toString();
            userData.userId=  jsonObject->value("data").toObject().value("sessionUser").toObject().value("userId").toInt();
            data->variant = QVariant::fromValue(userData);
         }
         else
             data->state =0;
    }break;

    case HttpFunction::LoginAccount: {
        _UserInfoData userData;
        userData.telephone = jsonObject->value("data").toObject().value("sessionUser").toObject().value("telephone").toString();
        userData.loginType = jsonObject->value("data").toObject().value("sessionUser").toObject().value("loginTye").toString();
        userData.loginTypeName = jsonObject->value("data").toObject().value("sessionUser").toObject().value("loginTypeName").toString();
        userData.roleName = jsonObject->value("data").toObject().value("sessionUser").toObject().value("roleName").toString();
        userData.userIconPath = jsonObject->value("data").toObject().value("sessionUser").toObject().value("userIconPath").toString();
        userData.userName = jsonObject->value("data").toObject().value("sessionUser").toObject().value("userName").toString();
        userData.userId=  jsonObject->value("data").toObject().value("sessionUser").toObject().value("userId").toInt();
        data->variant = QVariant::fromValue(userData);
    }break;

    case HttpFunction::GetQrCode: {
        _QrCoData qrcoData;
        qDebug()<< "qrcoData.url " << qrcoData.url <<Qt::endl;
        qrcoData.url = jsonObject->value("data").toObject().value("content").toString();
        qrcoData.uuid  =  jsonObject->value("data").toObject().value("uuid").toString();
        data->variant = QVariant::fromValue(qrcoData);
    }break;

    case HttpFunction::UploadCourseware:        //上传课件
    case HttpFunction::CheckRegistered:         //检查是否已经注册
    case HttpFunction::GetVerificationCode:     //发送验证码
    case HttpFunction::CheckVerificationCode:   //校验验证码
    case HttpFunction::RegisterAccount:         //注册账号
    case HttpFunction::UnBind:                  //解绑
    case HttpFunction::MobileSharing:           //手机分享
    default:
        break;
    }
}

void DB_HttpInterface::readReplyData()
{
    QByteArray bytes = m_pNetworkReply->readAll();
    QFile file(m_pSaveFilePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        file.write(bytes);
    }
    file.close();
}

void DB_HttpInterface::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit this->downloadProgress(bytesReceived, bytesTotal);
}
