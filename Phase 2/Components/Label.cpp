#include "Label.h"
#include <limits>
#include <sstream>

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

// Save format:
// LINE1: LABEL x1 y1 x2 y2
// LINE2: <label text>   (can contain spaces)
void Label::save(std::ofstream& file)
{
	// Write header + geometry on one line
	file << "LABEL " << m_GfxInfo.x1 << ' ' << m_GfxInfo.y1 << ' ' << m_GfxInfo.x2 << ' ' << m_GfxInfo.y2 << std::endl;
	// Write the label text on the next line (preserve spaces)
	file << label << std::endl;
}

void Label::load(std::ifstream& file)
{
	// Read coordinates
	int x1, y1, x2, y2;
	file >> x1 >> y1 >> x2 >> y2;
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	m_GfxInfo.x2 = x2;
	m_GfxInfo.y2 = y2;

	// consume the remaining end of line after the numbers so getline reads the label line
// Note the parentheses start BEFORE std:: and end AFTER ::max

	file.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	// Read the label text (may contain spaces)
	std::string tmp;
	std::getline(file, tmp);
	// Trim possible trailing '\r' from Windows line endings
	if (!tmp.empty() && tmp.back() == '\r') tmp.pop_back();
	label = tmp;
}

Label::~Label()
{
}