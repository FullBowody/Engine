#include "Serializable.hpp"
#include <memory>
#include "json.hpp"
#include "Structs/FBError.hpp"

std::shared_ptr<nlohmann::json> Serializable::serialize() const
{
    return onSerialize();
}

FBError Serializable::deserialize(const nlohmann::json& j)
{
    return onDeserialize(j);
}
