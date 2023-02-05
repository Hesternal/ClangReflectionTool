#pragma once

#include "HeaderTool/CppDesc.hpp"
#include "HeaderTool/CppWriter.hpp"


namespace HeaderTool
{

    class StructEmitter final
    {
    public:
        static void Emit(CppWriter& cppWriter, const std::vector<StructDesc>& structs);

    private:
        StructEmitter(CppWriter& cppWriter, const std::vector<StructDesc>& structs);
        ~StructEmitter() = default;

        void EmitInternal();

        void WriteEnumToStringFunction(const StructDesc& structDesc);

    private:
        CppWriter&                     m_cppWriter;
        const std::vector<StructDesc>& m_structs;
    };

} // namespace HeaderTool
