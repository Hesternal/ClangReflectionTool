#include "HeaderTool/CppDesc.hpp"
#include "HeaderTool/CppWriter.hpp"
#include "HeaderTool/EnumEmitter.hpp"
#include "HeaderTool/EnumParser.hpp"
#include "HeaderTool/StructEmitter.hpp"
#include "HeaderTool/StructParser.hpp"

// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"


namespace
{

    // Apply a custom category to all command-line options so that they are the only ones displayed.
    static llvm::cl::OptionCategory HeaderToolCategory("header-tool options");

    // CommonOptionsParser declares HelpMessage with a description of the common
    // command-line options related to the compilation database and input files.
    // It's nice to have this help message in all tools.
    // static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

    // A help message for this specific tool can be added afterwards.
    // static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");

} // namespace


int main(int argc, const char** argv)
{
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, HeaderToolCategory);
    if (!ExpectedParser) {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }

    clang::tooling::CommonOptionsParser& OptionsParser = ExpectedParser.get();

    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

    clang::ast_matchers::MatchFinder matchFinder;
    HeaderTool::EnumParser enumParser(matchFinder);
    HeaderTool::StructParser structParser(matchFinder);

    const int result = Tool.run(clang::tooling::newFrontendActionFactory(&matchFinder).get());

    HeaderTool::CppWriter cppWriter("Generated.cpp");
    cppWriter.WriteSystemInclude("string_view");
    cppWriter.WriteLines(2);

    HeaderTool::EnumEmitter::Emit(cppWriter, enumParser.GetEnums());
    cppWriter.WriteLine();
    HeaderTool::StructEmitter::Emit(cppWriter, structParser.GetStructs());

    return result;
}
