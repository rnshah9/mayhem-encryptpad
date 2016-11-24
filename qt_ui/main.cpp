//**********************************************************************************
//EncryptPad Copyright 2016 Evgeny Pokhilko 
//<http://www.evpo.net/encryptpad>
//
//This file is part of EncryptPad
//
//EncryptPad is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 2 of the License, or
//(at your option) any later version.
//
//EncryptPad is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with EncryptPad.  If not, see <http://www.gnu.org/licenses/>.
//**********************************************************************************
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QResource>
#include <QDirIterator>
#include <QLocale>
#include <string>
#include "mainwindow.h"
#include "application.h"

QString findLangResource(const QString &userLang)
{
    QString empty;
    QString lowerUserLang = userLang.toLower();
    if(lowerUserLang.indexOf('-') != -1)
    {
        lowerUserLang = lowerUserLang.left(lowerUserLang.indexOf('-'));
    }
    if(lowerUserLang.length() != 2)
        return empty;

    QString prefix = "encryptpad_";
    QDirIterator it(":/cultures/");
    while(it.hasNext())
    {
        QString fullPath = it.next();
        QString lang = it.fileName();
        if(lang.length() < prefix.length())
            return empty;

        lang = lang.right(lang.length() - prefix.length());
        if(lang.indexOf('_') == -1)
            return empty;

        lang = lang.left(lang.indexOf('_'));
        if(lang.length() != 2)
            return empty;

        if(lang == lowerUserLang)
            return fullPath;
    }

    return empty;
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(EncryptPad);

    Application app(argc, argv);

    QStringList userLangs = QLocale::system().uiLanguages();
    QString resourcePath;
    for(QString userLang : userLangs)
    {
        if(userLang == "en" || userLang.startsWith("en-"))
            break;
        resourcePath = findLangResource(userLang);
        if(!resourcePath.isEmpty())
            break;
    }

    QTranslator translator;

    if(!resourcePath.isEmpty())
    {
        QResource translator_res(resourcePath);
        bool result = translator.load(translator_res.data(), translator_res.size());
        assert(result);
        result = app.installTranslator(&translator);
        assert(result);
    }

    app.setOrganizationName("Evpo"); //
    app.setApplicationName("EncryptPad");

    QString fileName;
    if(app.arguments().length() > 1)
        fileName = app.arguments()[1];
    MainWindow mainWin;
    app.setMainWindow(&mainWin);
#if defined(Q_OS_SYMBIAN)
    mainWin.showMaximized();
#else
    mainWin.show();
#endif

    if(!fileName.isEmpty())
        mainWin.open(fileName);

    return app.exec();
}
//! [0]
