#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	
    QNetworkAccessManager*manger=new QNetworkAccessManager();
    qDebug()<<manger->supportedSchemes();
    //!设置代理
//    QNetworkProxy proxy;
//    proxy.setType(QNetworkProxy::HttpProxy);
//    proxy.setHostName("127.0.0.1");
//    proxy.setPort(8888);
//    manger->setProxy(proxy);
    QString baseUrl="http://192.168.5.84:28077/api/RailCrane/Cameras";
    QUrl url(baseUrl);
	//!设置请求参数
    QUrlQuery query;
    query.addQueryItem("name","0011");
    url.setQuery(query);
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply*pReplay=manger->get(request);
	//!消息阻塞
    QEventLoop eventLoop;
    QObject::connect(manger,&QNetworkAccessManager::finished,&eventLoop,&QEventLoop::quit);
    eventLoop.exec();
    //!响应状态码
    QVariant variant=pReplay->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(variant.isValid()){
        qDebug()<<variant.toInt();
    }
	//!处理数据
    QByteArray bytes=pReplay->readAll();
    QJsonParseError jsonError;
    QJsonDocument document=QJsonDocument::fromJson(bytes,&jsonError);
    if(jsonError.error!=QJsonParseError::NoError){
        qDebug()<<QStringLiteral("解析JSON失败");
    }
    qDebug()<<bytes;
    //!解析JSON
    if(document.isObject()){
        QJsonObject obj=document.object();
    }
    if(document.isArray()){
        QJsonArray objarry=document.array();
        for(int i=0;i<objarry.size();++i){
            QJsonValue value=objarry.at(i);
            if(value.isObject()){
                QJsonObject oj=value.toObject();
                qDebug()<<oj.take("IP").toString();
            }
        }
    }
    return a.exec();
}
