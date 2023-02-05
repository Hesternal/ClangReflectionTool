#pragma once

#include "HeaderTool/CppDesc.hpp"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"


namespace HeaderTool
{

    class StructParser final : public clang::ast_matchers::MatchFinder::MatchCallback
    {
    public:
        StructParser(clang::ast_matchers::MatchFinder& matchFinder);
        ~StructParser();

        StructParser(const StructParser&) = delete;
        StructParser& operator=(const StructParser&) = delete;

        [[nodiscard]] const std::vector<StructDesc>& GetStructs() const noexcept { return m_structs; }

    private:
        //< clang::ast_matchers::MatchFinder::MatchCallback
        void run(const clang::ast_matchers::MatchFinder::MatchResult& Result) override;
        //>

    private:
        std::vector<StructDesc> m_structs;
    };

} // namespace HeaderTool
