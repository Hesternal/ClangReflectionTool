#include "HeaderTool/MacroAttributes.hpp"

#include "clang/Basic/IdentifierTable.h" // for clang::IdentifierInfo
#include "clang/Lex/Token.h"             // for clang::Token


// https://stackoverflow.com/questions/70610120/how-to-use-custom-c-attributes-with-clang-libtooling-without-modifying-clang-c
// https://stackoverflow.com/questions/56512050/clang-how-to-get-the-macro-name-used-for-size-of-a-constant-size-array-declarat/56513459#56513459


namespace HeaderTool
{

    void MacroAttributes::MacroExpands(const clang::Token& MacroNameTok, const clang::MacroDefinition& MD, clang::SourceRange Range, const clang::MacroArgs* Args)
    {
        // Macro is not named for some reason.
        if (MacroNameTok.isAnyIdentifier() == false)
        {
            return;
        }

        if (MacroNameTok.getIdentifierInfo()->getName() == "CHT_STRUCT")
        {
            m_structMacros.push_back(Range);
        }
    }

} // namespace HeaderTool
