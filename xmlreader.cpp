#include "xmlreader.h"
XmlReader::XmlReader(QObject *parent) : QObject(parent)
{

}

bool XmlReader::ReadXmlFile(QString filePath)
{
    // Load xml file as raw data
    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly))
    {
        // Error while loading file
        return false;
    }
    // Set data into the QDomDocument before processing
    m_xmlDoc.setContent(&f);
    f.close();
    return true;
}

void XmlReader::ParserXml(MainModelServer* model)
{
    qDebug() << __func__;
    // Extract the root markup
    QDomElement root = m_xmlDoc.documentElement();

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component = root.firstChild().toElement();

    // Loop while there is a child
    while(!Component.isNull())
    {
        // Check if the child tag name is COMPONENT
        if (Component.tagName()=="APP")
        {

            // Read and display the component ID
            //QString ID = Component.attribute("ID","No ID");

            // Get the first child of the component
            QDomElement Child = Component.firstChild().toElement();

            QString name;
            QString server;
            QString username;
            QString password;
            QString connect;
            QString login;
            //Component.replaceChild()
            // Read each child of the component node
            while (!Child.isNull())
            {
                // Read Name and value
                if (Child.tagName()=="NAME")
                {
                    name = Child.firstChild().toText().data();
                }
                else if (Child.tagName()=="SERVER")
                {
                    server = Child.firstChild().toText().data();
                }
                else if (Child.tagName()=="USERNAME")
                {
                    username = Child.firstChild().toText().data();
                }
                else if (Child.tagName()=="PASSWORD")
                {
                    password = Child.firstChild().toText().data();
                }
                else if (Child.tagName()=="CONNECT")
                {
                    connect = Child.firstChild().toText().data();
                }
                else if (Child.tagName()=="LOGIN")
                {
                    login = Child.firstChild().toText().data();
                }
                // Next child
                Child = Child.nextSibling().toElement();
            }
            modelServer* item = new modelServer(name,server,username, password, connect, login); // vai chuong
//            model->addServer(new modelServer(name,server,username, password, connect, login));
            model->addServer(item);
        }
        qDebug() << __func__ << "END";
        // Next component
        Component = Component.nextSibling().toElement();
    }
}
