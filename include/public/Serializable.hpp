#pragma once
#include <memory>
#include "json.hpp"
#include "utils.hpp"
#include "Structs/FBError.hpp"

class DLLExport Serializable
{
protected:
    virtual std::shared_ptr<nlohmann::json> onSerialize() const = 0;
    virtual FBError onDeserialize(const nlohmann::json& j) = 0;
        
public:
    Serializable() = default;
    virtual ~Serializable() = default;

    std::shared_ptr<nlohmann::json> serialize() const;
    FBError deserialize(const nlohmann::json& j);
};
