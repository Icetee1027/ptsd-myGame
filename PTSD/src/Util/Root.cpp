#include "Util/Root.hpp"
#include "Core/Context.hpp"
#include <queue>
#include "Util/Time.hpp"
#include "Util/Logger.hpp"
namespace Util {
Root::Root(const std::vector<std::weak_ptr<GameObject>> children)
    : m_Children(children) {}

void Root::AddChild(const std::weak_ptr<GameObject> child) {
    m_Children.push_back(child);
}

void Root::RemoveChild(const std::weak_ptr<GameObject> child) {
    m_Children.erase(
        std::remove_if(m_Children.begin(), m_Children.end(),
                       [&child](const std::weak_ptr<GameObject> &element) {
                           return element.lock() == child.lock();
                       }),
        m_Children.end());
}

void Root::AddChildren(
    const std::vector<std::shared_ptr<GameObject>> &children) {
    m_Children.reserve(m_Children.size() + children.size());
    m_Children.insert(m_Children.end(), children.begin(), children.end());
}

void Root::Update() {
    
    if (!Core::Context::GetIsDraw())
        return;
    //if (1 / Util::Time::GetDeltaTime() < 50)
       // LOG_ERROR("{}", 1 / Util::Time::GetDeltaTime());
    struct StackInfo {
        std::shared_ptr<GameObject> m_GameObject;
        Transform m_ParentTransform;
    };

    std::vector<StackInfo> stack;
    stack.reserve(m_Children.size());

    std::vector<decltype(m_Children.begin())> invalidIterators;

    // 遍历 m_Children，检查 weak_ptr 是否有效，并记录无效元素的迭代器
    for (auto it = m_Children.begin(); it != m_Children.end(); ++it) {
        auto &weakChild = *it;
        if (auto sharedChild = weakChild.lock()) {
            stack.push_back(StackInfo{sharedChild, Transform{}});
        } else {
            // 如果 weakChild 无效，则记录要删除的迭代器
            invalidIterators.push_back(it);
        }
    }

    // 删除无效的元素
    
    for (auto it = invalidIterators.rbegin(); it != invalidIterators.rend(); ++it) {
        auto index = std::distance(m_Children.begin(), *it);
        m_Children.erase(m_Children.begin() + index);
        //LOG_ERROR("釋放root");
    }


    auto compareFunction = [](const StackInfo &a, const StackInfo &b) {
        return a.m_GameObject->GetZIndex() > b.m_GameObject->GetZIndex();
    };

    std::priority_queue<StackInfo, std::vector<StackInfo>,
                        decltype(compareFunction)>
        renderQueue(compareFunction);

    while (!stack.empty()) {
        auto curr = stack.back();
        stack.pop_back();
        renderQueue.push(curr);

        auto sharedCurr = curr.m_GameObject;
        for (const auto &child : sharedCurr->GetChildren()) {
            stack.push_back(StackInfo{child, sharedCurr->GetTransform()});
        }
    }

    // 按順序繪製 renderQueue 中的遊戲物件
    while (!renderQueue.empty()) {
        auto curr = renderQueue.top();
        renderQueue.pop();

        auto sharedCurr = curr.m_GameObject;
        sharedCurr->Draw();
    }
}



} // namespace Util
