#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>

using namespace Magnum;

namespace DroneControl {

    class Visualization: public Platform::Application {
        public:
            explicit Visualization(const Arguments& arguments);

        private:
            void drawEvent() override;

            GL::Mesh _mesh;
            Shaders::Phong _shader;

            Matrix4 _transformation, _projection;
            Color3 _color;
    };

    void startVisualization(int argc, char** argv);
}