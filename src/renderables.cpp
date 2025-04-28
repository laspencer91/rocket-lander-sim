#include "renderables.h"

/**
 * Gradient Box Wrapper.
 */
VGradientBox::VGradientBox(Vector2 position, Vector2 size, Color top_color, Color bottom_color):
    m_position(position),
    m_size(size),
    m_top_color(top_color),
    m_bottom_color(bottom_color) {}

void VGradientBox::Render() {
    DrawRectangleGradientV(m_position.x, m_position.y, m_size.x, m_size.y, m_top_color, m_bottom_color);
}

/**
 * MARS SCENE
 */
void MarsSceneGraphics::Render() {
    m_sky.Render();
    m_ground.Render();
}


