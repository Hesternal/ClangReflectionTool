#include "HeaderTool/EnumEmitter.hpp"


namespace HeaderTool
{

    void EnumEmitter::Emit(CppWriter& cppWriter, const std::vector<EnumDesc>& enums)
    {
        EnumEmitter(cppWriter, enums).EmitInternal();
    }


    EnumEmitter::EnumEmitter(CppWriter& cppWriter, const std::vector<EnumDesc>& enums)
        : m_cppWriter(cppWriter)
        , m_enums(enums)
    {}


    void EnumEmitter::EmitInternal()
    {
        for (const EnumDesc& enumDesc : m_enums)
        {
            WriteEnumToStringFunction(enumDesc);
        }
    }


    void EnumEmitter::WriteEnumToStringFunction(const EnumDesc& enumDesc)
    {
        m_cppWriter.Write("std::string_view ToString(");
        m_cppWriter.Write(enumDesc.Name);
        m_cppWriter.WriteLine(" value)");
        m_cppWriter.WriteStartBlock();

        m_cppWriter.WriteLine("switch (value)");
        m_cppWriter.WriteStartBlock();

        for (const EnumConstantDesc& enumConstantDesc : enumDesc.Constants)
        {
            m_cppWriter.Write(enumDesc.Name);
            m_cppWriter.Write("::");
            m_cppWriter.Write(enumConstantDesc.Name);
            m_cppWriter.Write(": return \"");
            m_cppWriter.Write(enumConstantDesc.Name);
            m_cppWriter.WriteLine("\";");
        }

        m_cppWriter.WriteEndBlock(); // switch

        m_cppWriter.WriteLine("return \"\";");
        m_cppWriter.WriteEndBlock(); // function
    }

} // namespace HeaderTool
