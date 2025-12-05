#include "Label.h"
Label::Label(const GraphicsInfo& r_GfxInfo,string label) {
	this->label = label;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}
 void Label::Draw(Output* pOut, bool selected ) {
	 pOut->DrawLabel(m_GfxInfo, selected,label);
 }

Label::~Label()
{
}