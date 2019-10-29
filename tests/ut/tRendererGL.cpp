#include <catch/catch.hpp>
#include <trompeloeil/trompeloeil.hpp>
#include "../../app/components/backend/Renderer.hpp"

using namespace rwc;
using trompeloeil::_;

struct RenderItemBase
{
    virtual ~RenderItemBase() = default;
    virtual void render(){};

    struct Buffer final
    {
        int mElements{0};
        unsigned mName{0};
    };
    struct VertexArray final
    {
        bool mActive{false};
        unsigned mName{0};
    };
    struct Texture final
    {
        unsigned mUnit{0};
        unsigned mName{0};
    };
    struct Attribute final
    {
        unsigned location{0};
        int count{0};
        unsigned type{0};
        int size{0};
        void* offset{nullptr};
        bool active{false};
    };
    Buffer mVBO{0};
    Buffer mIBO{0};
    VertexArray mVAO{false};
    unsigned mPO;
    unsigned mDrawType{0};
    std::vector<Attribute> mAttributes;
    std::vector<Texture> mTextures;
    std::map<std::string, Uniform> mUniforms;
};

struct RenderPassOne
{
    virtual ~RenderPassOne() = default;
    virtual void preRender(){};
    virtual void postRender(){};
};

struct RenderPassTwo
{
    virtual ~RenderPassTwo() = default;
    virtual void preRender(){};
    virtual void postRender(){};
};

class RenderItemOne : public RenderItemBase
{
public:
    MAKE_MOCK0(render, void());
};

TEST_CASE("Renderer with one render pass", "[OpenGL Renderer]")
{
    Renderer<RenderItemOne*, RenderPassOne> sut;
    std::vector<RenderItemOne*> items;
    std::unique_ptr<RenderItemOne> item = std::make_unique<RenderItemOne>();
    SECTION("Empty renderer with one render pass")
    {
        sut.addToRenderingPipeline<RenderPassOne>(items);
        REQUIRE_CALL(*(item.get()), render()).TIMES(0);
        sut.render();
    }

    SECTION("Not empty renderer with one render pass")
    {
        items.push_back(item.get());
        sut.addToRenderingPipeline<RenderPassOne>(items);
        REQUIRE_CALL(*(item.get()), render()).TIMES(1);
        sut.render();
    }

    SECTION("Two elements in renderer with one render pass")
    {
        items.push_back(item.get());
        items.push_back(item.get());
        sut.addToRenderingPipeline<RenderPassOne>(items);
        REQUIRE_CALL(*(item.get()), render()).TIMES(2);
        sut.render();
    }
}

TEST_CASE("Renderer with few render passes", "[OpenGL Renderer]")
{
    Renderer<RenderItemOne*, RenderPassOne, RenderPassTwo> sut;
    std::vector<RenderItemOne*> items;
    std::unique_ptr<RenderItemOne> item = std::make_unique<RenderItemOne>();
    SECTION("Empty renderer with two render passes")
    {
        sut.addToRenderingPipeline<RenderPassOne>(items);
        sut.addToRenderingPipeline<RenderPassTwo>(items);
        REQUIRE_CALL(*(item.get()), render()).TIMES(0);
        sut.render();
    }

    SECTION("Not empty renderer with two render passes")
    {
        items.push_back(item.get());
        sut.addToRenderingPipeline<RenderPassOne>(items);
        sut.addToRenderingPipeline<RenderPassTwo>(items);
        REQUIRE_CALL(*(item.get()), render()).TIMES(2);
        sut.render();
    }

    SECTION("Two same render items in renderer with two render passes")
    {
        items.push_back(item.get());
        sut.addToRenderingPipeline<RenderPassOne>(items);
        sut.addToRenderingPipeline<RenderPassOne>(items);
        sut.addToRenderingPipeline<RenderPassTwo>(items);
        sut.addToRenderingPipeline<RenderPassTwo>(items);
        REQUIRE_CALL(*(item.get()), render()).TIMES(4);
        sut.render();
    }

    SECTION("Two same render items in renderer with two render passes then cleared")
    {
        items.push_back(item.get());
        sut.addToRenderingPipeline<RenderPassOne>(items);
        sut.addToRenderingPipeline<RenderPassOne>(items);
        sut.addToRenderingPipeline<RenderPassTwo>(items);
        sut.addToRenderingPipeline<RenderPassTwo>(items);
        sut.clearRenderingPipeline();
        REQUIRE_CALL(*(item.get()), render()).TIMES(0);
        sut.render();
    }
}
