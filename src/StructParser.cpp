#include "HeaderTool/StructParser.hpp"

#include <utility>


namespace ast = clang::ast_matchers;


namespace
{

    static const llvm::StringRef StructMatcherID = "ScopedDefinedEnum";

    // NOTE(v.matushkin): ast::hasDefinition, ast::isDefinition ?

    static const ast::DeclarationMatcher StructMatcher = ast::cxxRecordDecl(
            ast::isStruct(),
            ast::hasDefinition(),
            ast::isExpansionInMainFile() // Without it I get too much noise
        ).bind(StructMatcherID);

} // namespace


namespace HeaderTool
{

    StructParser::StructParser(ast::MatchFinder& matchFinder)
    {
        matchFinder.addMatcher(StructMatcher, this);
    }

    StructParser::~StructParser() = default;


    void StructParser::run(const ast::MatchFinder::MatchResult& Result)
    {
        const auto* const structDecl = Result.Nodes.getNodeAs<clang::CXXRecordDecl>(StructMatcherID);
        if (structDecl == nullptr)
        {
            return;
        }

        const clang::RecordDecl::field_range structFields = structDecl->fields();
        if (structFields.empty())
        {
            return;
        }

        // structDecl->dump();

        StructDesc structDesc = {
            .Name = structDecl->getName().str(),
        };

        for (const clang::FieldDecl* const fieldDecl : structFields)
        {
            structDesc.Fields.emplace_back( // FieldDesc
                fieldDecl->getName().str()  // .Name
            );

            fieldDecl->getName();
        }

        m_structs.push_back(std::move(structDesc));
    }

} // namespace HeaderTool
