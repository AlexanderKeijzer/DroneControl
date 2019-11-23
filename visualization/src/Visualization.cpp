#include "Visualization.hpp"
#include <Magnum/GL/DefaultFramebuffer.h>

namespace DroneControl {

    Visualization::Visualization(const Arguments& arguments): Platform::Application{arguments} {
        /* TODO: Add your initialization code here */
    }

    void Visualization::drawEvent() {
        GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

        /* TODO: Add your drawing code here */

        swapBuffers();
    }
}
