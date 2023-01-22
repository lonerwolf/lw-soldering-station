//
// Created by lonerwolf on 2023/1/22.
//

#include "tools.h"

//数字范围映射
float tools_map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    return ((value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow);
}

