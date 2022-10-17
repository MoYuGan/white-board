#ifndef OCRWORKER_H
#define OCRWORKER_H

#include <QObject>
#include <QFile>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>
#include <QtDebug>

#include <curl/curl.h>
#include <stdio.h>
#include <string>
#include "cppcodec/base64_default_rfc4648.hpp"
#include "json.hpp"

using json = nlohmann::json;

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb,
                                 void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

class OCR_Worker: public QObject
{
    Q_OBJECT
public:
    OCR_Worker(QObject *parent = Q_NULLPTR)
        : QObject(parent)
    { }

    QStringList getWordList() {
        return m_pWordList;
    }

    void setPixmap(const QPixmap &pixmap) {
        m_pPixmap = pixmap;
    }


public slots:
    void startWorker()
    {
        // 常规配置
        std::string url =
            "https://tysbgpu.market.alicloudapi.com/api/predict/ocr_general";
        std::string appcode = "5bb27519c2b54a97809b40f1434f23fc";
        // 身份证配置 face or back
        std::string side = "back";


        // QPixmap转换成QByteArray
        QByteArray bytes;
        QBuffer buffer;
        buffer.open(QIODevice::ReadWrite);
        bool ok = m_pPixmap.save(&buffer, "jpg");
        if (!ok) {
            emit workFinished(-1);
            return;
        }
        bytes.append(buffer.data());
        // 将数据进行base64编码
        std::string image_code = base64::encode(bytes.data(), bytes.size());

        // if no configure, set as ""
        std::string configure = "{\"side\":\"" + side + "\"}";
        std::string body = composeJson(image_code, configure);
        if (!httpPost(url, appcode, body)) {
            emit workFinished(-1);
            return;
        }

        emit workFinished(1);
        return;
    }

private:
    std::string composeJson(const std::string &imageCode,
                           const std::string &configure) {
     json body;
     if (configure.size() > 0) body["configure"] = configure;
     body["image"] = imageCode;
     return body.dump();
     //return QString::fromStdString(body.dump());
   }

   void getTextFromJson(QByteArray bytes) {
       QJsonParseError jsonError;
       QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
       if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
       {
           QJsonObject object = doucment.object();
           QJsonArray retList = object.value("ret").toArray();
           for (int i = 0; i < retList.size(); i++) {
               m_pWordList.append(retList[i].toObject().value("word").toString());
           }
       }
   }

    bool httpPost(const std::string &url, const std::string &appcode,
                        const std::string &body) {
       bool ret = true;
       CURL *curl;
       CURLcode res;
       curl = curl_easy_init();
       if (curl) {
           struct MemoryStruct response;
           response.memory =(char*) malloc(1);
           response.size = 0;

           struct curl_slist *custom_header = NULL;
           custom_header = curl_slist_append(
               custom_header, std::string("Authorization:APPCODE " + appcode).c_str());
           custom_header = curl_slist_append(
               custom_header, "Content-Type:application/json; charset=UTF-8");
           res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, custom_header);

           curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
           curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
           curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
           curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
           curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
           // comment this line to ignore reponse header
           curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
           curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

           res = curl_easy_perform(curl);
           long http_code = 0;
           long header_size = 0;
           curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
           curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &header_size);

           if (res != CURLE_OK) {
             //printf("post failed %s\n", curl_easy_strerror(res));
             ret = false;
           } else {
             if (http_code != 200) {
               //printf("http code: %ld\n", http_code);
               char buf[header_size];
               memcpy(buf, response.memory, header_size);
               //printf("%s\n", buf);
             }
             getTextFromJson(QByteArray(response.memory + header_size));
            //printf("----%s\n", response.memory + header_size);
           }

           curl_easy_cleanup(curl);
           free(response.memory);
           curl_slist_free_all(custom_header);
           curl_global_cleanup();
       }
       return ret;
   }

private:
    QStringList m_pWordList;
    QPixmap m_pPixmap;

signals:
    void workFinished(int);
};

#endif // OCRWORKER_H
