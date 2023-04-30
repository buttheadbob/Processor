#pragma once
#include <vector>

using namespace System;
using namespace System::Collections::Generic;

namespace NumaInfo {

    public ref class ProcessorInfo
    {
    public:
        static List<int>^ GetNumaNodeInformation();
    };

}


