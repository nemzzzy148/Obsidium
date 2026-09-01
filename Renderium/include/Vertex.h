//
// Created by Nemesis Verstraete on 12/08/2026.
//

#pragma once
#include <cstddef>
#include <string>

namespace renderium {
class Shader;

enum class VertexFormat {
    Float32,
    Float32x2,
    Float32x3
};

struct VertexAttribute {
    VertexFormat format;
    std::size_t size;
};

struct VertexBufferLayout {
    size_t vertexStride;
    size_t attributeCount;
    VertexAttribute attributes[];
};

struct VertexState {
    Shader* shader;
    EntryPointType entryPointType = EntryPointType::AttributeIndication;
    // only necessary with function name entry point indication
    std::string functionEntryPointName = "";
    Buffer* buffer = nullptr;
};

}
