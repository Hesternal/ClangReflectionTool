#include "HeaderTool/CppWriter.hpp"


namespace HeaderTool
{

    CppWriter::CppWriter(const std::string& codeFilePath)
        : CodeWriter(codeFilePath)
    {}


    void CppWriter::WriteSystemInclude(std::string_view include)
    {
        Write("#include <");
        Write(include);
        WriteLine('>');
    }


    void CppWriter::WriteStartBlock()
    {
        WriteLine('{');
        PushIndent();
    }

    void CppWriter::WriteEndBlock()
    {
        PopIndent();
        WriteLine('}');
    }

    void CppWriter::WriteStartNamespace(std::string_view namespace_)
    {
        Write("namespace ");
        Write(namespace_);
        WriteStartBlock();
    }

    void CppWriter::WriteEndNamespace()
    {
        WriteEndBlock();
    }

} // namespace HeaderTool
