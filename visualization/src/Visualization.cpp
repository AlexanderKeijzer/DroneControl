#include "Visualization.hpp"
#include "simulation.hpp"
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData3D.h>
#include <mutex>

extern std::mutex objectMutex;

namespace DroneControl {

using namespace Magnum::Math::Literals;

    Visualization::Visualization(const Arguments& arguments): Platform::Application{arguments} {
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
        GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

        const Trade::MeshData3D cube = Primitives::cubeSolid();

        GL::Buffer vertices;
        vertices.setData(MeshTools::interleave(cube.positions(0), cube.normals(0)));

        Containers::Array<char> indexData;
        MeshIndexType indexType;
        UnsignedInt indexStart, indexEnd;
        std::tie(indexData, indexType, indexStart, indexEnd) =
            MeshTools::compressIndices(cube.indices());
        GL::Buffer indices;
        indices.setData(indexData);

        _mesh.setPrimitive(cube.primitive())
            .setCount(cube.indices().size())
            .addVertexBuffer(std::move(vertices), 0, Shaders::Phong::Position{},
                                                    Shaders::Phong::Normal{})
            .setIndexBuffer(std::move(indices), 0, indexType, indexStart, indexEnd);

        _transformation =
            Matrix4::rotationX(30.0_degf)*Matrix4::rotationY(40.0_degf);
        _projection =
            Matrix4::perspectiveProjection(
                35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f)*
            Matrix4::translation(Vector3::zAxis(-10.0f));
        _color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});
    }

    void Visualization::drawEvent() {
        GL::defaultFramebuffer.clear(
            GL::FramebufferClear::Color|GL::FramebufferClear::Depth);


        {
            std::lock_guard<std::mutex> guard(objectMutex);
            const std::vector<Object*> objects = getObjects();
            if (!objects.empty()) {
                WorldObject* drone = dynamic_cast<WorldObject*>(objects[0]);
                Vec3 pos = drone->getPos();
                Vec3 rot = drone->getRot();
                pos.display();
                _transformation = Matrix4::translation(Vector3(pos.getX(), pos.getZ(), pos.getY()))*Matrix4::rotationX(Rad(rot.getX()))*Matrix4::rotationY(Rad(rot.getY()))*Matrix4::rotationZ(Rad(rot.getZ()));
            }
        }

        _shader.setLightPosition({7.0f, 5.0f, 2.5f})
            .setLightColor(Color3{1.0f})
            .setDiffuseColor(_color)
            .setAmbientColor(Color3::fromHsv({_color.hue(), 1.0f, 0.3f}))
            .setTransformationMatrix(_transformation)
            .setNormalMatrix(_transformation.normalMatrix())
            .setProjectionMatrix(_projection);
        _mesh.draw(_shader);

        swapBuffers();
        redraw();
    }

    void startVisualization(int argc, char** argv) {
        Visualization app({argc, argv});
        app.exec();
    }
}
