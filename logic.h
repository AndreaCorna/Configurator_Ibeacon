#ifndef LOGIC_H
#define LOGIC_H
#include <QtCore>

class logic:  public QObject
{
     Q_OBJECT
public:
    logic
    logic(const logic &); // hide copy constructor
    logic& operator=(const logic &);
    void generate(QString uuid, QString major, QString minor);

signals:
        void update();

private:


};

#endif // LOGIC_H
