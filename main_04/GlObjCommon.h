
#include "GlObj.h"

class GlObjCommon :
    public GlObj
{

public:
    GlObjCommon();

    void init(void) override;
    void init(float* vertices, int vsize, int mode, float *color, int csize, QString vert, QString frag) override;

    void draw(void) override;

};

