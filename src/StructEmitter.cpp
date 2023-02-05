#include "HeaderTool/StructEmitter.hpp"


namespace HeaderTool
{

    void StructEmitter::Emit(CppWriter& cppWriter, const std::vector<StructDesc>& structs)
    {
        StructEmitter(cppWriter, structs).EmitInternal();
    }


    StructEmitter::StructEmitter(CppWriter& cppWriter, const std::vector<StructDesc>& structs)
        : m_cppWriter(cppWriter)
        , m_structs(structs)
    {}


    void StructEmitter::EmitInternal()
    {
        for (const StructDesc& structDesc : m_structs)
        {
            WriteEnumToStringFunction(structDesc);
        }
    }


    void StructEmitter::WriteEnumToStringFunction(const StructDesc& structDesc)
    {
        m_cppWriter.Write("IBinaryConverter& operator<<(IBinaryConverter& bc, ");
        m_cppWriter.Write(structDesc.Name);
        m_cppWriter.WriteLine("& value)");
        m_cppWriter.WriteStartBlock();

        for (const FieldDesc& structFieldDesc : structDesc.Fields)
        {
            // bc << value.Name;
            m_cppWriter.Write("bc << value.");
            m_cppWriter.Write(structFieldDesc.Name);
            m_cppWriter.WriteLine(';');
        }

        m_cppWriter.WriteLine("return bc;");
        m_cppWriter.WriteEndBlock(); // function
    }

} // namespace HeaderTool
