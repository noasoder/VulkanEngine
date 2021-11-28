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

private:
    Engine* m_pEngine;

    NetHandler* m_pNetHandler;
};

#endif // !APPLICATION_H