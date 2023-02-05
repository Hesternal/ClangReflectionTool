#include "HeaderTool/EnumParser.hpp"

#include <utility>


namespace ast = clang::ast_matchers;


namespace
{

    static const llvm::StringRef EnumMatcherID = "ScopedDefinedEnum";

    static const ast::DeclarationMatcher EnumMatcher = ast::enumDecl(
            ast::isScoped(),
            ast::isExpansionInMainFile()
        ).bind(EnumMatcherID);

} // namespace


namespace HeaderTool
{

    EnumParser::EnumParser(ast::MatchFinder& matchFinder)
    {
        matchFinder.addMatcher(EnumMatcher, this);
    }

    EnumParser::~EnumParser() = default;


    void EnumParser::run(const ast::MatchFinder::MatchResult& Result)
    {
        const auto* const enumDecl = Result.Nodes.getNodeAs<clang::EnumDecl>(EnumMatcherID);
        if (enumDecl == nullptr)
        {
            return;
        }

        const clang::EnumDecl::enumerator_range enumConstants = enumDecl->enumerators();
        if (enumConstants.empty())
        {
            return;
        }

        // enumDecl->dump();

        // NOTE(v.matushkin):
        //   Why the fuck this works -> enumDesc.Name = enumDecl->getName();
        //   And this doesn't        -> EnumDesc enumDesc = { .Name = enumDecl->getName() };

        // NOTE(v.matushkin): How should I get the enum underlying type?
        //   It looks like EnumDecl::getIntegerType is the choice, but even then, should I pass any arguments to this method?

        // NOTE(v.matushkin): No way to get enumerators count and reserve memory for EnumDesc::Constants ?

        EnumDesc enumDesc = {
            .Name           = enumDecl->getName().str(),
            .UnderlyingType = enumDecl->getIntegerType().getAsString(),
        };

        // NOTE(v.matushkin): There is a helper toString() function that converts APSInt to std::string in "llvm/ADT/StringExtras.h"
        //   But I can reuse SmallString here.
        llvm::SmallString<40> constantValueStr;

        for (const clang::EnumConstantDecl* const enumConstantDecl : enumConstants)
        {
            enumConstantDecl->getInitVal().toString(constantValueStr);

            enumDesc.Constants.emplace_back(       // EnumConstantDesc
                enumConstantDecl->getName().str(), // .Name
                std::string(constantValueStr)      // .Value
            );

            constantValueStr.clear();
        }

        m_enums.push_back(std::move(enumDesc));
    }

} // namespace HeaderTool
