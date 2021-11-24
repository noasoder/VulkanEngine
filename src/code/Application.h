#ifndef APPLICATION_H
#define APPLICATION_H

class Engine;
class NetHandler;

class Application
{
public:
    Application();
    ~Application();
    void Run();
    void CloseApplication();

private:
    bool m_Running;

    Engine* m_pEngine;

    NetHandler* m_pNetHandler;
};

#endif // !APPLICATION_H