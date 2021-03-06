/*
 *  Qactus - A Qt based OBS notifier
 *
 *  Copyright (C) 2013-2018 Javier Llorente <javier@opensuse.org>
 *  Copyright (C) 2010-2011 Sivan Greenberg <sivan@omniqueue.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OBSACCESS_H
#define OBSACCESS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QAuthenticator>
#include <QNetworkReply>
#include <QSslError>
#include <QDebug>
#include <QEventLoop>
#include "obsxmlreader.h"

class OBSXmlReader;

class OBSAccess : public QObject
{
     Q_OBJECT

public:
    static OBSAccess* getInstance();
    bool isAuthenticated();
    QString getUsername();
    void request(const QString &urlStr);
    QNetworkReply *postRequest(const QString &urlStr, const QByteArray &data);
    void getProjects(const QString &urlStr);
    void getProjectMetadata(const QString &urlStr);
    void getPackages(const QString &urlStr);
    void getFiles(const QString &urlStr);
    void getAllBuildStatus(const QString &urlStr);
    void changeSubmitRequest(const QString &urlStr, const QByteArray &data);
    void request(const QString &urlStr, const int &row);
    void getSRDiff(const QString &urlStr);

signals:
    void isAuthenticated(bool authenticated);
    void selfSignedCertificate(QNetworkReply *reply);
    void networkError(const QString &error);
    void srDiffFetched(const QString &diff);

public slots:
    void setCredentials(const QString&, const QString&);

private slots:
    void provideAuthentication(QNetworkReply* reply, QAuthenticator* ator);
    void replyFinished(QNetworkReply* reply);
    void onSslErrors(QNetworkReply* reply, const QList<QSslError> &list);

private:
/*
 * We need to instantiate QNAM only once, as it should be used as
 * as singleton or a utility instead of recreating it for each
 * request. This class (OBSAccess) uses the singleton pattern to
 * achieve this.
 *
 */
    QNetworkAccessManager* manager;
    void createManager();
    OBSAccess();
    static OBSAccess* instance;
    QString curUsername;
    QString curPassword;
    QNetworkReply *browseRequest(const QString &urlStr);
    enum RequestType {
        ProjectList,
        ProjectMetadata,
        PackageList,
        FileList,
        BuildStatusList,
        SubmitRequest,
        SRDiff
    };
    bool authenticated;
    OBSXmlReader *xmlReader;
};

#endif // OBSACCESS_H
