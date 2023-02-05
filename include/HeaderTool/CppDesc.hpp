#pragma once

#include <string>
#include <vector>


namespace HeaderTool
{

    struct EnumConstantDesc final
    {
        std::string Name;
        std::string Value;
    };

    struct EnumDesc final
    {
        std::string                   Name;
        std::string                   UnderlyingType;
        std::vector<EnumConstantDesc> Constants;
    };


    struct FieldDesc final
    {
        std::string Name;
    };

    struct StructDesc final
    {
        std::string            Name;
        std::vector<FieldDesc> Fields;
    };

} // namespace HeaderTool
