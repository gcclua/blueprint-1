#include "blueprint/Blueprint.h"
#include "blueprint/CompNode.h"
#include "blueprint/NSCompNode.h"
#include "blueprint/Node.h"
#include "blueprint/node/Commentary.h"
#include "blueprint/node/SetLocalVar.h"
#include "blueprint/node/GetLocalVar.h"

#include <ns/CompIdxMgr.h>
#include <ns/RegistCallback.h>
#include <node2/RenderSystem.h>
#include <node2/UpdateSystem.h>
#include <node2/CompTransform.h>
#include <node2/AABBSystem.h>

namespace bp
{

CU_SINGLETON_DEFINITION(Blueprint);

extern void regist_rttr();

Blueprint::Blueprint()
{
	Init();
	InitNodes();
}

void Blueprint::Init()
{
	regist_rttr();

	// node serializer
	ns::CompIdxMgr::Instance()->AddExtTypeToIdx(CompNode::TYPE_NAME, ns::COMP_INVALID);
	ns::RegistCallback::AddUniqueCB<CompNode, NSCompNode>();

	// node2
	n2::RenderSystem::Instance()->AddDrawCompFunc(
		[](const n0::SceneNode& node, const n2::RenderParams& rp)
	{
		if (node.HasUniqueComp<CompNode>()) {
			auto& cnode = node.GetUniqueComp<CompNode>();
			cnode.GetNode()->Draw(rp.GetMatrix());
		}
	});
	n2::UpdateSystem::Instance()->AddUpdateCompFunc([](const n0::SceneNode& node)->bool
	{
		if (!node.HasUniqueComp<CompNode>()) {
			return false;
		}

		auto& cnode = node.GetUniqueComp<CompNode>();
		auto& ctrans = node.GetUniqueComp<n2::CompTransform>();
		auto& pos = ctrans.GetTrans().GetPosition();
		return cnode.GetNode()->SetPos(pos);
	});
	n2::AABBSystem::Instance()->AddGetBoundFunc([](const n0::SceneNode& node, sm::rect& bound)->bool
	{
		if (!node.HasUniqueComp<CompNode>()) {
			return false;
		}

		auto& cnode = node.GetUniqueComp<CompNode>();
		auto& st = cnode.GetNode()->GetStyle();
		bound.Build(st.width, st.height);
		return true;
	});
}

void Blueprint::InitNodes()
{
    //auto list = rttr::type::get<Node>().get_derived_classes();
    //m_nodes.reserve(list.size());
    //for (auto& t : list)
    //{
    //    auto obj = t.create();
    //    assert(obj.is_valid());
    //    auto node = obj.get_value<bp::NodePtr>();
    //    assert(node);
    //    m_nodes.push_back(node);
    //}
    
    m_nodes.push_back(std::make_shared<node::Commentary>());
    m_nodes.push_back(std::make_shared<node::SetLocalVar>());
    m_nodes.push_back(std::make_shared<node::GetLocalVar>());
}

}