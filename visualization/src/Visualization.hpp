#include <Magnum/Platform/Sdl2Application.h>

using namespace Magnum;

namespace DroneControl {

    class Visualization: public Platform::Application {
        public:
            explicit Visualization(const Arguments& arguments);

        private:
            void drawEvent() override;
    };

}