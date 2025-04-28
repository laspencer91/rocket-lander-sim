#ifndef APPLICATION_H
#define APPLICATION_H
#include <any>
#include <raylib.h>
#include <vector>

#include "irenderable.h"
#include "iupdateable.h"

class Application
{
public:
    Application();
    ~Application();

    void Initialize(int winW, int winH);
    void Run();

private:
    void Update(float dt);
    void Render();
    void Shutdown();

    std::vector<IRenderable*> m_renderables;
    std::vector<IUpdateable*> m_updateables;
    Camera m_camera;
};

#endif //APPLICATION_H
