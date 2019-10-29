#pragma once

#include <Moveable.hpp>
#include "../../../backend/RenderItem.hpp"
#include <memory>

namespace rwc
{

/*
 * @class Node3D
 *
 * @Bbrief Base 3D node tree entity
 */
class Node3D : public Moveable
{
public:
    Node3D(
        const RenderItem& renderItem
        , const glm::vec3& translation = glm::vec3(0.0)
        , const glm::quat& rotation = glm::quat(1.0, 0.0, 0.0, 0.0)
        , const glm::vec3& scale = glm::vec3(1.0f));

    ~Node3D() override;
/*
 * @brief Supposed to be called every frame. Updates the objects
 *        internal state and related program object uniforms
 */
    virtual void onUpdate();

/*
 * @brief Gets information how many render items are pinned to this node
 *
 * @return number of render items including own render item and all children render items
 *
 */
    unsigned getRenderItemsCount() const;

/*
 * @brief Gets render items pinned to this node
 *
 * @param [out] renderItems including own renderItems and children render items
 *
 */
    void getRenderItems(std::vector<RenderItem>& renderItems) const;

/*
 * @brief Gets the render item
 *
 * @return render item of this node
 *
 */
    const RenderItem& getRenderItem() const;

/*
 * @brief Attach children node
 *
 * @param Node3D unique pointer keeping a different instance of Scene node
 *
 */
    void attach(std::unique_ptr<Node3D>&& node);

/*
 * @brief call all onUpdate Callbacks for each node
 *
 */
    void update();

/*
 * @brief Update all internal matrices
 *
 */
    void updateTransformations();

/*
 * @brief Update parent matrix so that global transformation for each element in tree will be correct
 *
 * @param [in] parent matrix used to compute transformation global matrix of each scene node
 *
 */
    void updateParentMatrix(const glm::mat4& parent);

/*
 * @brief Update parent matrix so that global rotation for each element in tree will be correct
 *
 * @param [in] parent rotation which will be saved as parents one
 *
 */
    void updateParentRotation(const glm::quat& parent);

/*
 * @brief Return global transformation including parents transformations
 *        It necessary to manually update all matrices if needed before
 *        calling this function by callin updateTransformations
 *
 * @return node transformation matrix
 *
 */
    const glm::mat4& getCurrentTransformation() const;

/*
 * @brief perform all time dependent animations.
 *
 * @param [in] timeSinceLastFrameInSeconds time since last frame in seconds
 */
    void onTimePassedSec(float timeSinceLastFrameInSeconds);

/*
 * @brief perform all time dependent animations.
 *
 * @param [in] callback to execute against its owner
 */
    void onChildrenCallback(std::function<void(Node3D&)> callback);

protected:
    glm::mat4 mMMCGlobal;
    bool mMMCParentRefresh;
    RenderItem mRenderItem;
    std::vector<std::unique_ptr<Node3D>> mChildren;
};

} // namespace rwc
