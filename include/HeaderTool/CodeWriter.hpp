#pragma once

#include "HeaderTool/Core.hpp"

#include <fstream>
#include <string>
#include <string_view>


namespace HeaderTool
{

    class CodeWriter
    {
    public:
        ~CodeWriter() = default;

        CodeWriter(const CodeWriter&) = delete;
        CodeWriter& operator=(const CodeWriter&) = delete;
        CodeWriter(CodeWriter&& other) noexcept = default;
        CodeWriter& operator=(CodeWriter&& other) noexcept = default;

        void Write(char value);
        void Write(std::string_view value);

        void WriteLine();
        void WriteLine(char value);
        void WriteLine(std::string_view value);
        void WriteLines(int32 lines);

    protected:
        CodeWriter(const std::string& codeFilePath);

        void PushIndent() noexcept;
        void PopIndent() noexcept;

    private:
        void WriteIndent();

    protected:
        std::ofstream m_codeWriter;

    private:
        int32 m_indentLevel;
        int32 m_indentSpaces;
        bool  m_shouldIndent;
    };

} // namespace HeaderTool
