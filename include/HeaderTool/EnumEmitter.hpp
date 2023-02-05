#pragma once

#include "HeaderTool/CppDesc.hpp"
#include "HeaderTool/CppWriter.hpp"


namespace HeaderTool
{

    class EnumEmitter final
    {
    public:
        static void Emit(CppWriter& cppWriter, const std::vector<EnumDesc>& enums);

    private:
        EnumEmitter(CppWriter& cppWriter, const std::vector<EnumDesc>& enums);
        ~EnumEmitter() = default;

        void EmitInternal();

        void WriteEnumToStringFunction(const EnumDesc& enumDesc);

    private:
        CppWriter&                   m_cppWriter;
        const std::vector<EnumDesc>& m_enums;
    };

} // namespace HeaderTool
