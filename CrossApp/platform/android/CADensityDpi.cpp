
#include "platform/CADensityDpi.h"
#include "jni/JniHelper.h"
#include <jni.h>

NS_CC_BEGIN
float CADensityDpi::getDensityDpi()
{
    static float ret = -1;
    
    if (ret != -1)
    {
        return ret;
    }
    
    JniMethodInfo jni;
    if(!JniHelper::getStaticMethodInfo(jni , "org/CrossApp/lib/CrossAppHelper" , "getDPI" , "()F"))
    {
        return DPI_STANDARD;
    }
    
    ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID , jni.methodID);
    jni.env->DeleteLocalRef(jni.classID);

    return ret;
}

CADeviceIdiom CADensityDpi::getIdiom()
{
    return CADeviceIdiomPhone;
}

NS_CC_END