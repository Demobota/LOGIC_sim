#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
}
GraphicsInfo Component::GetGFXinfo() {
	return m_GfxInfo;
}
void Component::SetSelect() {
	selected = (selected ==true)?false:true;
}
bool Component::GetSelect() {

	return selected;
}

Component::Component(){}
Component::~Component()
{}

