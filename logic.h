#ifndef LOGIC_H
#define LOGIC_H
#include <QMutex>

class logic
{
public:
    static logic* instance()
        {
            static QMutex mutex;
            if (!m_Instance)
            {
                mutex.lock();

                if (!m_Instance)
                    m_Instance = new logic;

                mutex.unlock();
            }

            return m_Instance;
        }

        static void drop()
        {
            static QMutex mutex;
            mutex.lock();
            delete m_Instance;
            m_Instance = 0;
            mutex.unlock();
        }

private:
    logic(){};
    logic(const logic &); // hide copy constructor
    logic& operator=(const logic &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident

    static logic* m_Instance;

};

#endif // LOGIC_H
