#ifndef RENDERABLES_H
#define RENDERABLES_H
#include <raylib.h>

#include "irenderable.h"


class VGradientBox: public IRenderable {
public:
    VGradientBox(Vector2 position, Vector2 size, Color top_color, Color bottom_color);

    void Render() override;

private:
    Vector2 m_position{};
    Vector2 m_size{};
    Color m_top_color;
    Color m_bottom_color;
};


class MarsSceneGraphics: public IRenderable {
public:
    void Render() override;

private:
    const Color MARS_SKY_SPACE = { 5, 5, 24, 255 };        // #050518 - Dark space blue
    const Color MARS_SKY_HORIZON = { 240, 127, 79, 255 };  // #F07F4F - Salmon orange
    // Mars Ground Colors (from surface to depth)
    const Color MARS_GROUND_SURFACE = { 217, 167, 106, 255 }; // #D9A76A - Sandy tan
    const Color MARS_GROUND_BASE = { 74, 38, 38, 255 };      // #4A2626 - Dark maroon

    VGradientBox m_sky = VGradientBox(Vector2(0, 0), Vector2(GetScreenWidth(), GetScreenHeight()), MARS_SKY_SPACE,
                         MARS_SKY_HORIZON);
    VGradientBox m_ground = VGradientBox(Vector2(0, GetScreenHeight() * 0.75),
                                               Vector2(GetScreenWidth(), GetScreenHeight() - GetScreenHeight() * 0.75),
                                               MARS_GROUND_SURFACE, MARS_GROUND_BASE);
};


#endif //RENDERABLES_H
