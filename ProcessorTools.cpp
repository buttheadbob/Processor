#include "pch.h"
#include "stdafx.h"
#include "ProcessorTools.h"

namespace ProcessorTools
{
    namespace ProcessorInfo
    {
        void NumaInfo::ShowNumaNodeInformation()
        {
            ULONG nodeCount = 0;
            ULONG processorCount = 0;
            PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX pslpi = NULL;
            SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer;
            DWORD returnLength = 0;
            DWORD byteOffset = 0;
            DWORD i;

            // First, retrieve the size of the buffer required to store information about the logical processors
            BOOL result = GetLogicalProcessorInformationEx(RelationNumaNode, NULL, &returnLength);
            if (result == FALSE && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            {
                throw std::runtime_error("Could not retrieve logical processor information");
            }

            // Allocate the buffer to store the logical processor information
            pslpi = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)malloc(returnLength);
            if (pslpi == NULL)
            {
                throw std::runtime_error("Could not allocate buffer for logical processor information");
            }

            // Retrieve the logical processor information
            result = GetLogicalProcessorInformationEx(RelationNumaNode, pslpi, &returnLength);
            if (result == FALSE)
            {
                free(pslpi);
                throw std::runtime_error("Could not retrieve logical processor information");
            }

            for (i = 0; byteOffset < returnLength; i++)
            {
                PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX ptr = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)((PBYTE)pslpi + byteOffset);
                byteOffset += ptr->Size;

                if (ptr->Relationship == RelationNumaNode)
                {
                    PUCHAR nodeStr = (PUCHAR)&ptr->NumaNode.NodeNumber;
                    printf("Node %hhu:\n", ptr->NumaNode.NodeNumber);
                    printf("\tProcessor Mask: 0x%llx\n", ptr->NumaNode.ProcessorMask);
                    printf("\tNode ID: %02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x\n", nodeStr[0], nodeStr[1], nodeStr[2], nodeStr[3], nodeStr[4], nodeStr[5], nodeStr[6], nodeStr[7]);
                    printf("\tDistance: %u\n", ptr->NumaNode.Distance);
                }
            }

            free(pslpi);
        }
    }
}

