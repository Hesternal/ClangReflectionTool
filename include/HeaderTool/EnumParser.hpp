#pragma once

#include "HeaderTool/CppDesc.hpp"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"


namespace HeaderTool
{

    class EnumParser final : public clang::ast_matchers::MatchFinder::MatchCallback
    {
    public:
        EnumParser(clang::ast_matchers::MatchFinder& matchFinder);
        ~EnumParser();

        EnumParser(const EnumParser&) = delete;
        EnumParser& operator=(const EnumParser&) = delete;
        //EnumParser(EnumParser&& other) noexcept;
        //EnumParser& operator=(EnumParser&& other) noexcept;

        [[nodiscard]] const std::vector<EnumDesc>& GetEnums() const noexcept { return m_enums; }

    private:
        //< clang::ast_matchers::MatchFinder::MatchCallback
        void run(const clang::ast_matchers::MatchFinder::MatchResult& Result) override;
        //>

    private:
        std::vector<EnumDesc> m_enums;
    };

} // namespace HeaderTool
