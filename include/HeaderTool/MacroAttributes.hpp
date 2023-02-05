#pragma once

#include <vector>

#include "clang/Lex/PPCallbacks.h"


namespace HeaderTool
{

    class MacroAttributes final : clang::PPCallbacks
    {
    public:
        MacroAttributes() = default;
        ~MacroAttributes() = default;

        [[nodiscard]] const std::vector<clang::SourceRange> GetStructMacros() const noexcept { return m_structMacros; }

    private:
        void MacroExpands(const clang::Token& MacroNameTok, const clang::MacroDefinition& MD, clang::SourceRange Range, const clang::MacroArgs* Args) override;

    private:
        std::vector<clang::SourceRange> m_structMacros;
    };

} // namespace HeaderTool
