#pragma once

#include <Windows.h>
#include <vector>
#include <string>

class ProcessorTools
{
public:
    static std::vector<BYTE> GetNumaNodeInformation();
    static std::vector<std::string> GetProcessorAffinityList();
    static std::vector<std::string> GetNumaNodeAffinityList();
    static std::vector<std::string> GetProcessorNumaNodeList();
    static std::vector<std::string> GetProcessorNumaNodeAffinityList();
    static ULONGLONG GetProcessorNumaNodeAffinity(ULONG ProcessorIndex);
    static ULONGLONG GetProcessorNumaNodeAffinity(PROCESSOR_NUMBER ProcessorNumber);
    static DWORD GetNumaNodeCount();
    static DWORD GetProcessorCount();
    static DWORD GetProcessorCount(DWORD NumaNode);
    static DWORD GetNumaNode(ULONG ProcessorIndex);
    static DWORD GetNumaNode(PROCESSOR_NUMBER ProcessorNumber);
private:
    static ULONGLONG GetProcessorAffinity(ULONG ProcessorIndex);
};
