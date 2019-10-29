#include <nodes/Node3D.hpp>

namespace rwc
{

Node3D::Node3D(const RenderItem& renderItem, const glm::vec3& translation, const glm::quat& rotation, const glm::vec3& scale)
    : Moveable{translation, rotation, scale}
    , mMMCGlobal{mMMC}
    , mMMCParentRefresh{true}
    , mRenderItem{renderItem}
    , mChildren{}
{
    updateTransformations();
}

Node3D::~Node3D() = default;

void Node3D::onUpdate()
{
    // empty
}

unsigned Node3D::getRenderItemsCount() const
{
    unsigned count = 1;
    for (const auto& child : mChildren)
    {
        count += child->getRenderItemsCount();
    }
    return count;
}

void Node3D::getRenderItems(std::vector<RenderItem>& renderItems) const
{
    renderItems.push_back(mRenderItem);
    for (const auto& it : mChildren)
    {
        it->getRenderItems(renderItems);
    }
}

const RenderItem& Node3D::getRenderItem() const
{
    return mRenderItem;
}

void Node3D::attach(std::unique_ptr<Node3D>&& node)
{
    mRefresh = true;
    mChildren.push_back(std::move(node));
}

void Node3D::update()
{
    onUpdate();
    for (auto& child : mChildren)
    {
        child->update();
    }
}

void Node3D::updateTransformations()
{
    if (mRefresh)
    {
        updateMatrixCache();
        mMMCParentRefresh = true;
        mRefresh = false;
    }

    if (mMMCParentRefresh)
    {
        mMMCGlobal = mParentMMC * mMMC;
        for (auto& it : mChildren) {
            it->updateParentMatrix(mMMCGlobal);
        }
        mMMCParentRefresh = false;
    }

    for (auto& it : mChildren)
    {
        it->updateTransformations();
    }
}

void Node3D::updateParentMatrix(const glm::mat4& parent)
{
    mParentMMC = parent;
    mMMCGlobal = mParentMMC * mMMC;
    mMMCParentRefresh = true;
}

void Node3D::updateParentRotation(const glm::quat& parent)
{
    mParentRotation = parent;
    glm::quat localRotation(mParentRotation * mRotation);
    for (auto& child : mChildren)
    {
        child->updateParentRotation(localRotation);
    }
}
const glm::mat4& Node3D::getCurrentTransformation() const
{
    return mMMCGlobal;
}

void Node3D::onTimePassedSec(float timeSinceLastFrameInSeconds)
{
    Moveable::onTimePassed(timeSinceLastFrameInSeconds);
    for (auto& child : mChildren)
    {
        child->onTimePassedSec(timeSinceLastFrameInSeconds);
    }
}

void Node3D::onChildrenCallback(std::function<void(Node3D&)> callback)
{
    callback(*this);
    for (auto& child : mChildren)
    {
        child->onChildrenCallback(callback);
    }
}

} // namespace rwc
