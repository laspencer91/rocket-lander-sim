#include "application.h"

int main() {
    auto app = Application();
    app.Initialize(800, 600);
    app.Run();
    return 0;
}