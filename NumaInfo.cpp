#include "stdafx.h"
#include <windows.h>
#include <vector>

#pragma comment(lib, "Kernel32.lib")

using namespace NumaInfo;
using namespace System::Collections::Generic;

List<int>^ ProcessorInfo::GetNumaNodeInformation()
{
    List<int>^ nodeInformation = gcnew List<int>();

    ULONG processorCount = 0;
    ULONG numaNodeCount = 0;

    GetSystemProcessorInfo(&processorCount, &numaNodeCount);

    PROCESSOR_NUMBER processorNumber = { 0 };
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX processorInformation = NULL;
    ULONG processorInformationSize = 0;

    for (ULONG i = 0; i < processorCount; i++) {
        processorInformationSize = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
        processorInformation = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)malloc(processorInformationSize);

        if (processorInformation == NULL) {
            break;
        }

        ZeroMemory(processorInformation, processorInformationSize);
        processorNumber.Group = 0;
        processorNumber.Number = i;

        if (KeQueryLogicalProcessorRelationship(&processorNumber, RelationNumaNode, processorInformation, &processorInformationSize) == STATUS_SUCCESS) {
            nodeInformation->Add((int)processorInformation->NumaNode.NodeNumber);
        }

        free(processorInformation);
    }

    return nodeInformation;
}
