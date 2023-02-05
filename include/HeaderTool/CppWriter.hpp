#pragma once

#include "HeaderTool/CodeWriter.hpp"

#include <string>
#include <string_view>


namespace HeaderTool
{

    class CppWriter final : public CodeWriter
    {
    public:
        CppWriter(const std::string& codeFilePath);

        CppWriter(CppWriter&& other) noexcept = default;
        CppWriter& operator=(CppWriter&& other) noexcept = default;

        void WriteSystemInclude(std::string_view include);

        void WriteStartBlock();
        void WriteEndBlock();
        void WriteStartNamespace(std::string_view namespace_);
        void WriteEndNamespace();
    };

} // namespace HeaderTool
