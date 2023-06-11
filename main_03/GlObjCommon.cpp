#include "GlObjCommon.h"

GlObjCommon::GlObjCommon()
{

}

void GlObjCommon::init(void)
{
}

void GlObjCommon::init(float* vertices, int vsize, int mode, float *color, int csize, QString vert, QString frag)
{
	_init(vertices, vsize, mode, color, csize, vert, frag);
}

void GlObjCommon::draw(void)
{
	glDrawArrays(m_mode, 0, m_vsize);
}
