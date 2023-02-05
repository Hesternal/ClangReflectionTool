#include "HeaderTool/CodeWriter.hpp"


namespace
{
    using namespace HeaderTool;


    static constexpr int32 k_IndentSize = 4;
    static constexpr std::string_view k_IndentString = "                                                ";

} // namespace


namespace HeaderTool
{

    CodeWriter::CodeWriter(const std::string& codeFilePath)
        : m_codeWriter(codeFilePath)
        , m_indentLevel(0)
        , m_indentSpaces(0)
        , m_shouldIndent(false)
    {}


    void CodeWriter::Write(char value)
    {
        WriteIndent();
        m_codeWriter << value;
    }

    void CodeWriter::Write(std::string_view value)
    {
        WriteIndent();
        m_codeWriter << value;
    }


    void CodeWriter::WriteLine()
    {
        m_codeWriter << '\n';
        m_shouldIndent = true;
    }

    void CodeWriter::WriteLine(char value)
    {
        Write(value);
        WriteLine();
    }

    void CodeWriter::WriteLine(std::string_view value)
    {
        Write(value);
        WriteLine();
    }

    void CodeWriter::WriteLines(int32 lines)
    {
        for (int32 i = 0; i < lines; i++)
        {
            m_codeWriter << '\n';
        }
        m_shouldIndent = true;
    }


    void CodeWriter::PushIndent() noexcept
    {
        m_indentSpaces = ++m_indentLevel * k_IndentSize;
    }

    void CodeWriter::PopIndent() noexcept
    {
        m_indentSpaces = --m_indentLevel * k_IndentSize;
    }


    void CodeWriter::WriteIndent()
    {
        if (m_shouldIndent)
        {
            m_shouldIndent = false;
            m_codeWriter.write(k_IndentString.data(), m_indentSpaces);
        }
    }

} // namespace HeaderTool
