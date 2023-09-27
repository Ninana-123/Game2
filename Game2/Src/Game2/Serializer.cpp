#include "pch.h"
//#include "Serializer.h"
//#include "EngineTypes.h"
//#include <utility>
//
//namespace Engine
//{
//    std::string Serializer::SerializeEntity(const Entity& entity)
//    {
//        rapidjson::StringBuffer s;
//        rapidjson::Writer<rapidjson::StringBuffer> writer(s);
//
//        writer.StartObject();
//        writer.Key("EntityID");
//        writer.Uint64(entity.GetID());
//        //writer.Key("Health");
//        //writer.Double(entity.GetComponent(ComponentType::Health));
//        writer.Key("PositionX");
//       // writer.Double(entity.GetComponent(ComponentType::Position)->GetValueX());
//        writer.Key("PositionY");
//        //writer.Double(entity.GetComponent(ComponentType::Position)->GetValueY());
//        writer.EndObject();
//
//        return s.GetString();
//    }
//
//    Entity Serializer::DeserializeEntity(const std::string& json)
//    {
//        EntityID entityID = 0;
//        //double health = 0.0;
//        double posX = 0.0;
//        double posY = 0.0;
//
//        rapidjson::Document doc;
//        doc.Parse(json.c_str());
//
//        if (!doc.IsObject())
//        {
//            // Handle invalid JSON
//            return Entity(-1); // Return an error entity
//        }
//
//        if (doc.HasMember("EntityID") && doc["EntityID"].IsUint64())
//        {
//            entityID = doc["EntityID"].GetUint64();
//        }
//
//        /*if (doc.HasMember("Health") && doc["Health"].IsDouble())
//        {
//            health = doc["Health"].GetDouble();
//        }*/
//
//        if (doc.HasMember("PositionX") && doc["PositionX"].IsDouble()
//            && doc.HasMember("PositionY") && doc["PositionY"].IsDouble())
//        {
//            posX = doc["PositionX"].GetDouble();
//            posY = doc["PositionY"].GetDouble();
//        }
//
//        // Create and return the entity with the parsed data
//        Entity entity(entityID);
//        //entity.AddComponent(std::make_unique<HealthComponent>(health));
//        //entity.AddComponent(ComponentType::Position);
//
//        return entity;
//    }
//}