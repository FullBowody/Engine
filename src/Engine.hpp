class Engine
{
public:
    Engine();
    ~Engine();

    virtual int start();
    virtual int update(float dt);
    virtual int stop();
};
