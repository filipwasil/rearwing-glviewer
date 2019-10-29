#include <catch/catch.hpp>
#include <trompeloeil/trompeloeil.hpp>
#include <nodes/Node3D.hpp>

using namespace rwc;
using trompeloeil::_;

class TestNode : public Node3D
{
public:
    TestNode()
        : Node3D({})
    {

    }
    MAKE_MOCK0(onUpdate, void());
};

TEST_CASE("Gathering elements for renderer should always return proper number of items", "[Node3D]")
{
    RenderItem renderItem;
    std::array<std::unique_ptr<Node3D>, 3> sut;
    std::unique_ptr<Node3D> root;
    SECTION("Empty scene has only one render item")
    {
        root = std::make_unique<Node3D>(renderItem);

        CHECK(1 == root->getRenderItemsCount());
        std::vector<RenderItem> renderItems;
        root->getRenderItems(renderItems);
        CHECK(1 == renderItems.size());
    }

    SECTION("Non empty scene has one render item plus one for each children", "[Node3D]")
    {
        root = std::make_unique<Node3D>(renderItem);
        sut[0] = std::make_unique<Node3D>(renderItem);
        sut[1] = std::make_unique<Node3D>(renderItem);
        sut[2] = std::make_unique<Node3D>(renderItem);

        sut[1]->attach(std::move(sut[0]));
        sut[2]->attach(std::move(sut[1]));
        root->attach(std::move(sut[2]));
        CHECK(4 == root->getRenderItemsCount());
        std::vector<RenderItem> renderItems;
        root->getRenderItems(renderItems);
        CHECK(4 == renderItems.size());
    }
}

TEST_CASE("updating children updates also all the parents", "[Node3D]")
{
    std::array<std::unique_ptr<TestNode>, 3> sut;
    std::unique_ptr<Node3D> root;
    SECTION("Calling update on parent calls update on all its children")
    {
        RenderItem renderItem;
        root = std::make_unique<Node3D>(renderItem);
        sut[0] = std::make_unique<TestNode>();
        sut[1] = std::make_unique<TestNode>();
        sut[2] = std::make_unique<TestNode>();
        auto& sutPtr1 = *(sut[0].get());
        auto& sutPtr2 = *(sut[1].get());
        auto& sutPtr3 = *(sut[2].get());
        root->attach(std::move(sut[0]));
        root->attach(std::move(sut[1]));
        root->attach(std::move(sut[2]));
        REQUIRE_CALL(sutPtr1, onUpdate()).TIMES(1);
        REQUIRE_CALL(sutPtr2, onUpdate()).TIMES(1);
        REQUIRE_CALL(sutPtr3, onUpdate()).TIMES(1);
        root->update();
    }

    SECTION("Calling update on parent calls update on all children of its children")
    {
        root = std::make_unique<Node3D>(RenderItem{});
        sut[0] = std::make_unique<TestNode>();
        sut[1] = std::make_unique<TestNode>();
        sut[2] = std::make_unique<TestNode>();
        auto& sutPtr1 = *(sut[0].get());
        auto& sutPtr2 = *(sut[1].get());
        auto& sutPtr3 = *(sut[2].get());
        sut[1]->attach(std::move(sut[0]));
        sut[2]->attach(std::move(sut[1]));
        root->attach(std::move(sut[2]));
        REQUIRE_CALL(sutPtr1, onUpdate()).TIMES(1);
        REQUIRE_CALL(sutPtr2, onUpdate()).TIMES(1);
        REQUIRE_CALL(sutPtr3, onUpdate()).TIMES(1);
        root->update();
    }

    SECTION("Refresh needed when adding a child")
    {
        root = std::make_unique<Node3D>(RenderItem{});
        auto child = std::make_unique<Node3D>(RenderItem{});
        root->attach(std::move(child));
        CHECK(root->isRefresh());
    }
}