#pragma once

#include <ee0/AtomicOP.h>
#include <ee0/typedef.h>

namespace bp
{

class Pin;

class DisconnectConnAO : public ee0::AtomicOP
{
public:
    DisconnectConnAO(const ee0::SubjectMgrPtr& sub_mgr, 
        const std::shared_ptr<Pin>& from, const std::shared_ptr<Pin>& to);

    virtual void Undo() override;
    virtual void Redo() override;

private:
    ee0::SubjectMgrPtr m_sub_mgr;

    std::shared_ptr<Pin> m_from, m_to;

}; // DisconnectConnAO

}